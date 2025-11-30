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
#ifndef _NIXL_TELEMETRY_EXPORTER_H
#define _NIXL_TELEMETRY_EXPORTER_H

#include <cstdint>
#include <cstring>
#include <string>

#include "nixl_types.h"
#include "telemetry_event.h"

struct nixlTelemetryExporterInitParams {
    std::string agentName;
    size_t maxEventsBuffered;
};

class nixlTelemetryExporter {
public:
    explicit nixlTelemetryExporter(const nixlTelemetryExporterInitParams &init_params)
        : agent_ame_(init_params.agentName),
          buffer_size_(init_params.maxEventsBuffered) {}

    virtual ~nixlTelemetryExporter() = default;

    virtual nixl_status_t
    exportEvent(const nixlTelemetryEvent &event) = 0;

    [[nodiscard]] size_t
    getBufferSize() const noexcept {
        return buffer_size_;
    }

    [[nodiscard]] std::string_view
    getAgentName() const noexcept {
        return agent_ame_;
    }

private:
    const std::string_view agent_ame_;
    const int buffer_size_;
};

#endif // _NIXL_TELEMETRY_EXPORTER_H
