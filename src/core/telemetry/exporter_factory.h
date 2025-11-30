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
#ifndef _NIXL_EXPORTER_FACTORY_H
#define _NIXL_EXPORTER_FACTORY_H

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include "telemetry_exporter.h"

class ExporterFactory {
public:
    using ExporterCreator = std::function<std::unique_ptr<nixlTelemetryExporter>(
        const nixlTelemetryExporterInitParams &)>;

    /**
     * @brief Get singleton instance of the factory
     */
    static ExporterFactory &
    getInstance();

    void
    registerExporter(const std::string &typeName, ExporterCreator creator);

    std::unique_ptr<nixlTelemetryExporter>
    createExporter(const std::string &typeName, const nixlTelemetryExporterInitParams &params);

private:
    ExporterFactory();
    void
    registerBuiltinExporters();

    std::unordered_map<std::string, ExporterCreator> creators_;
};

#endif // _NIXL_EXPORTER_FACTORY_H
