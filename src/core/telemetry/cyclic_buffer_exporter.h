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
#ifndef _NIXL_CYCLIC_BUFFER_EXPORTER_H
#define _NIXL_CYCLIC_BUFFER_EXPORTER_H

#include <string>
#include <fstream>
#include <memory>
#include <filesystem>

#include "telemetry_exporter.h"
#include "telemetry_event.h"
#include "nixl_types.h"
#include "common/cyclic_buffer.h"

class nixlCyclicBufferExporter : public nixlTelemetryExporter {
public:
    explicit nixlCyclicBufferExporter(const nixlTelemetryExporterInitParams &init_params);

    ~nixlCyclicBufferExporter() override = default;

    /**
     * @brief Export a telemetry event to the cyclic buffer
     * @param event The telemetry event to export
     * @return NIXL_SUCCESS on success
     */
    nixl_status_t
    exportEvent(const nixlTelemetryEvent &event) override;

private:
    std::unique_ptr<sharedRingBuffer<nixlTelemetryEvent>> buffer_;
};

#endif // _NIXL_CYCLIC_BUFFER_EXPORTER_H
