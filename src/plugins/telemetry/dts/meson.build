# SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# DTS (DOCA Telemetry Service) exporter plugin

dts_lib_path = '/opt/mellanox/doca'
dts_inc_path = dts_lib_path / 'include'
dts_lib_dir = dts_lib_path / 'lib/x86_64-linux-gnu'

# Check if DTS library exists
if not fs.is_dir(dts_inc_path)
    warning('DTS include directory not found at: ' + dts_inc_path)
    warning('Skipping DTS telemetry exporter plugin')
    subdir_done()
endif

# Create DTS dependency
dts_dep = declare_dependency(
    include_directories: include_directories(dts_inc_path),
    link_args: [
        '-L' + dts_lib_dir,
        '-ldoca_telemetry_exporter',
        '-ldoca_common',
        '-Wl,-rpath,' + dts_lib_dir
    ]
)

telemetry_exporter_dts_sources = [
    'dts_exporter.cpp',
    'dts_plugin.cpp',
]

shared_library('telemetry_exporter_dts',
    sources: telemetry_exporter_dts_sources,
    include_directories: [nixl_inc_dirs, utils_inc_dirs],
    dependencies: [nixl_common_dep, thread_dep, dts_dep],
    install: true,
    install_dir: get_option('libdir') / 'nixl' / 'telemetry',
    gnu_symbol_visibility: 'hidden',
)

