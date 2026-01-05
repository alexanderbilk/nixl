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
#ifndef _TELEMETRY_DTS_EXPORTER_H
#define _TELEMETRY_DTS_EXPORTER_H

#include "telemetry/telemetry_exporter.h"
#include "telemetry_event.h"
#include "nixl_types.h"

#include <doca_telemetry_exporter.h>
#include <string>
#include <memory>
#include <mutex>

/**
 * @class nixlTelemetryDTSExporter
 * @brief DOCA Telemetry Service (DTS) exporter implementation
 *
 * This class implements the telemetry exporter interface to export
 * telemetry events to DOCA Telemetry Service.
 */
class nixlTelemetryDTSExporter : public nixlTelemetryExporter {
public:
    /**
     * @brief Constructor using init params (plugin-compatible)
     * @param init_params Initialization parameters
     */
    explicit nixlTelemetryDTSExporter(const nixlTelemetryExporterInitParams &init_params);

    /**
     * @brief Destructor - cleans up DOCA resources
     */
    ~nixlTelemetryDTSExporter() override;

    /**
     * @brief Export a telemetry event to DTS
     * @param event The telemetry event to export
     * @return NIXL_SUCCESS on success, error code otherwise
     */
    nixl_status_t
    exportEvent(const nixlTelemetryEvent &event) override;

private:
    const bool local_ = false;
    const uint16_t port_;
    bool initialized_ = false;
    const std::string agent_name_;
    const std::string hostname_;
    doca_telemetry_exporter_schema *schema_ = nullptr;
    doca_telemetry_exporter_source *source_ = nullptr;
    doca_telemetry_exporter_label_set_id_t label_set_id_ = 0;
    std::mutex mutex_;
    std::string bind_address_;

    /**
     * @brief Initialize DOCA schema and source
     * @return NIXL_SUCCESS on success, error code otherwise
     */
    nixl_status_t
    initializeDoca(const nixlTelemetryExporterInitParams &params);

    doca_error_t
    registerCounter(const nixlTelemetryEvent &event, const char *label_values[]);

    doca_error_t
    registerGauge(const nixlTelemetryEvent &event, const char *label_values[]);
};

#endif // _TELEMETRY_DTS_EXPORTER_H
