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
#include "cyclic_buffer_exporter.h"
#include "common/nixl_log.h"

constexpr char telemetryDirVar[] = "NIXL_TELEMETRY_DIR";

nixlCyclicBufferExporter::nixlCyclicBufferExporter(
    const nixlTelemetryExporterInitParams &init_params)
    : nixlTelemetryExporter(init_params) {
    if (init_params.agentName.empty()) {
        throw std::invalid_argument("Agent name cannot be empty");
    }

    const char *telemetry_env_dir = std::getenv(telemetryDirVar);
    if (telemetry_env_dir == nullptr) {
        throw std::invalid_argument("Telemetry directory cannot be empty");
    }

    std::string output_path = std::string(telemetry_env_dir) + "/" + init_params.agentName;
    buffer_ = std::make_unique<sharedRingBuffer<nixlTelemetryEvent>>(
        output_path, true, TELEMETRY_VERSION, init_params.maxEventsBuffered);

    NIXL_INFO << "Telemetry enabled, using buffer path: " << output_path
              << " with size: " << getBufferSize();
}

nixl_status_t
nixlCyclicBufferExporter::exportEvent(const nixlTelemetryEvent &event) {
    if (!buffer_->push(event)) {
        return NIXL_ERR_UNKNOWN;
    }

    return NIXL_SUCCESS;
}
