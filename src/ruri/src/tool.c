// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2022-2024 Moe-hacker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 */
#include "include/ruri.h"
// Umount container.
void umount_container(const char *container_dir)
{
	// Do not use '/' for container_dir.
	if (strcmp(container_dir, "/") == 0) {
		error("\033[31mError: `/` is not allowed to use as a container directory QwQ\n");
	}
	char mountpoint[MAX_MOUNTPOINTS / 2][PATH_MAX];
	mountpoint[0][0] = '\0';
	// Get path to umount.
	char sys_dir[PATH_MAX];
	char proc_dir[PATH_MAX];
	char dev_dir[PATH_MAX];
	char to_umountpoint[PATH_MAX];
	strcpy(sys_dir, container_dir);
	strcpy(proc_dir, container_dir);
	strcpy(dev_dir, container_dir);
	strcat(sys_dir, "/sys");
	strcat(proc_dir, "/proc");
	strcat(dev_dir, "/dev");
	printf("\033[1;38;2;254;228;208mUmount container.\033[0m\n");
	// Umount other mountpoints.
	for (int i = 0; true; i++) {
		if (mountpoint[i][0] != 0) {
			strcpy(to_umountpoint, container_dir);
			strcat(to_umountpoint, mountpoint[i]);
			for (int j = 0; j < 10; j++) {
				umount2(to_umountpoint, MNT_DETACH | MNT_FORCE);
				umount(to_umountpoint);
				usleep(20000);
			}
		} else {
			break;
		}
	}
	// Force umount system runtime directories for 10 times.
	for (int i = 1; i < 10; i++) {
		umount2(sys_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
		umount2(dev_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
		umount2(proc_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
		umount2(container_dir, MNT_DETACH | MNT_FORCE);
		usleep(20000);
	}
}
