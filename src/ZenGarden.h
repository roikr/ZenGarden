/*
 *  Copyright 2010 Reality Jockey, Ltd.
 *                 info@rjdj.me
 *                 http://rjdj.me/
 * 
 *  This file is part of ZenGarden.
 *
 *  ZenGarden is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ZenGarden is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with ZenGarden.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _ZENGARDEN_H_
#define _ZENGARDEN_H_

/**
 * This header file defines the C interface to ZenGarden to the outside world. Include this header
 * along with the <code>libzengarden</code> library in your project in order to integrate it.
 */
#ifdef __cplusplus
class PdGraph;
typedef PdGraph ZGGraph;
extern "C" {
#else
  typedef void ZGGraph;
#endif
  
  /** Create a new graph with the given parameters. */
  ZGGraph *zg_new_graph(char *directory, char *filename, int blockSize, 
      int numInputChannels, int numOutputChannels, float sampleRate);
  
  /** Delete the given graph. */
  void zg_delete_graph(ZGGraph *graph);
  
  /** Process the given graph. */
  void zg_process(ZGGraph *graph, float *inputBuffers, float *outputBuffers);
  
  /**
   * Send a message to the named receiver with the given format at the beginning of the next audio block.
   * E.g., zg_send_message(graph, "#accelerate", "fff", 0.0f, 0.0f, 0.0f);
   * sends a message containing three floats, each with value 0.0f, to all receivers named "#accelerate".
   * Messages may also be formatted with "s" and "b" for symbols and bangs, respectively.
   * E.g., zg_send_message(graph, "test", "s", "hello");
   * E.g., zg_send_message(graph, "test", "b");
   */
  void zg_send_message(ZGGraph *graph, const char *receiveName, const char *messageFormat, ...);
  
#ifdef __cplusplus
}
#endif

#endif // _ZENGARDEN_H_