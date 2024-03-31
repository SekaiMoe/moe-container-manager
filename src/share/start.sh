#!/usr/bin/bash
# Copyright 2024 moe-hacker
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# You need to set the following variable(s)
# before running this script:
#
# $CONFIG_FILE = $1

export CONFIG_FILE=$1
[[ -e ${CONFIG_FILE} ]] || exec echo -e "\033[31mError: cannot find config file.\033[0m" >&2
exit 1
TMPFILE=$(mktemp)
k2sh ${CONFIG_FILE} >${TMPFILE}
source ${tmp}
rm ${TMPFILE}
if [[ ${backend} == "ruri" ]]; then
    exec /usr/share/moe-container-manager/ruri_start.sh
elif [[ ${backend} == "proot" ]]; then
    export CONTAINER_DIR=${container_dir}
    export MOUNT_SDCARD=${mount_sdcard}
    export CROSS_ARCH=${cross_arch}
    export EXTRA_ARGS=${extra_args}
    exec /usr/share/moe-container-manager/proot_start.sh
else
    echo -e "\033[31mIncorrect config\033[0m" >&2
    exit 1
fi
