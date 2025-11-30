/*
 * SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "exporter_factory.h"
#include "cyclic_buffer_exporter.h"
#include "common/nixl_log.h"

#include <algorithm>
#include <stdexcept>

ExporterFactory::ExporterFactory() {
    registerBuiltinExporters();
}

ExporterFactory &
ExporterFactory::getInstance() {
    static ExporterFactory instance;

    return instance;
}

void
ExporterFactory::registerBuiltinExporters() {
    // Register cyclic buffer exporter (default)
    registerExporter("buffer", [](const nixlTelemetryExporterInitParams &params) {
        return std::make_unique<nixlCyclicBufferExporter>(params);
    });
}

void
ExporterFactory::registerExporter(const std::string &typeName, ExporterCreator creator) {
    // Convert to lowercase for case-insensitive matching
    std::string lowerName = typeName;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    creators_[lowerName] = creator;
    NIXL_DEBUG << "Registered telemetry exporter: " << typeName;
}

std::unique_ptr<nixlTelemetryExporter>
ExporterFactory::createExporter(const std::string &typeName,
                                const nixlTelemetryExporterInitParams &params) {
    // Convert to lowercase for case-insensitive matching
    std::string lowerName = typeName;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    auto it = creators_.find(lowerName);
    if (it == creators_.end()) {
        throw std::runtime_error("Unknown telemetry exporter type: '" + typeName + "'");
    }

    NIXL_INFO << "Creating telemetry exporter of type: " << typeName;
    return it->second(params);
}
