/******************************************************************************
    Copyright (C) 2013 by Hugh Bailey <obs.jim@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#pragma once

#include "../util/c99defs.h"
#include "media-io.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Base audio output component.  Use this to create an audio output track
 * for the media.
 */

struct audio_output;
struct audio_line;
typedef struct audio_output *audio_t;
typedef struct audio_line   *audio_line_t;

enum audio_type {
	AUDIO_FORMAT_UNKNOWN,
	AUDIO_FORMAT_8BIT,
	AUDIO_FORMAT_16BIT,
	AUDIO_FORMAT_24BIT,
	AUDIO_FORMAT_32BIT,
	AUDIO_FORMAT_FLOAT,
};

enum speaker_setup {
	SPEAKERS_UNKNOWN,
	SPEAKERS_MONO,
	SPEAKERS_STEREO,
	SPEAKERS_2POINT1,
	SPEAKERS_QUAD,
	SPEAKERS_4POINT1,
	SPEAKERS_5POINT1,
	SPEAKERS_5POINT1_SURROUND,
	SPEAKERS_7POINT1,
	SPEAKERS_7POINT1_SURROUND,
	SPEAKERS_SURROUND,
};

struct audio_data {
	const void      *data;
	uint32_t        frames;
	uint64_t        timestamp;
};

struct audio_info {
	const char         *name;
	const char         *format;

	uint32_t           samples_per_sec;
	enum audio_type    type;
	enum speaker_setup speakers;
};


static inline uint32_t get_audio_channels(enum speaker_setup speakers)
{
	switch (speakers) {
	case SPEAKERS_MONO:             return 1;
	case SPEAKERS_STEREO:           return 2;
	case SPEAKERS_2POINT1:          return 3;
	case SPEAKERS_SURROUND:
	case SPEAKERS_QUAD:             return 4;
	case SPEAKERS_4POINT1:          return 5;
	case SPEAKERS_5POINT1:
	case SPEAKERS_5POINT1_SURROUND: return 6;
	case SPEAKERS_7POINT1:          return 8;
	case SPEAKERS_7POINT1_SURROUND: return 8;
	case SPEAKERS_UNKNOWN:          return 0;
	}

	return 0;
}

static inline size_t get_audio_bytes_per_channel(enum audio_type type)
{
	switch (type) {
	case AUDIO_FORMAT_8BIT:    return 1;
	case AUDIO_FORMAT_16BIT:   return 2;
	case AUDIO_FORMAT_24BIT:   return 3;
	case AUDIO_FORMAT_FLOAT:
	case AUDIO_FORMAT_32BIT:   return 4;
	case AUDIO_FORMAT_UNKNOWN: return 0;
	}

	return 0;
}

static inline size_t get_audio_size(enum audio_type type,
		enum speaker_setup speakers, uint32_t frames)
{
	return get_audio_channels(speakers) *
	       get_audio_bytes_per_channel(type) *
	       frames;
}

#define AUDIO_OUTPUT_SUCCESS       0
#define AUDIO_OUTPUT_INVALIDPARAM -1
#define AUDIO_OUTPUT_FAIL         -2

EXPORT int audio_output_open(audio_t *audio, media_t media,
		struct audio_info *info);
EXPORT audio_line_t audio_output_createline(audio_t audio);
EXPORT size_t audio_output_blocksize(audio_t audio);
EXPORT const struct audio_info *audio_output_getinfo(audio_t audio);
EXPORT void audio_output_close(audio_t audio);

EXPORT void audio_line_destroy(audio_line_t line);
EXPORT void audio_line_output(audio_line_t line, const struct audio_data *data);

#ifdef __cplusplus
}
#endif
