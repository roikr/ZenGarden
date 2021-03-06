/*
 *  Copyright 2009,2010 Reality Jockey, Ltd.
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

#ifndef _PD_GRAPH_H_
#define _PD_GRAPH_H_

#include <stdio.h>
#include "DspObject.h"
#include "OrderedMessageQueue.h"
#include "PdFileParser.h"
#include "ZGCallbackFunction.h"

class DelayReceiver;
class DspCatch;
class DspDelayWrite;
class DspReceive;
class DspSend;
class DspThrow;
class MessageObject;
class MessageReceive;
class MessageSend;
class MessageSendController;

class PdGraph : public DspObject {
  
  public:
    static PdGraph *newInstance(char *directory, char *filename, int blockSize,
        int numInputChannels, int numOutputChannels, float sampleRate, PdGraph *parentGraph);
    ~PdGraph();
  
    /**
     * Register the callback function which will be used to programmetically communicate with
     * the outside world.
     */
    void registerCallback(void (*function)(ZGCallbackFunction, void *, void *), void *userData);
    
    /**
     * Schedules a <code>PdMessage</code> to be sent by the <code>MessageObject</code> from the
     * <code>outletIndex</code> at the specified <code>time</code>.
     */
    void scheduleMessage(MessageObject *messageObject, int outletIndex, PdMessage *message);
  
    /** Cancel a scheduled <code>PdMessage</code> according to its id. */
    void cancelMessage(MessageObject *messageObject, int outletIndex, PdMessage *message);
  
    /* 
     * Messages arriving at <code>PdGraph</code>s are processed immediately (passed on to inlet
     * objects, unlike with super-<code>DspObject</code> objects.
     */
    void receiveMessage(int inletIndex, PdMessage *message);
  
    /** Receives and processes messages sent to the Pd system by sending to "pd". */
    void receiveSystemMessage(PdMessage *message);
  
    void processMessage(int inletIndex, PdMessage *message);
    
    /* This functions implements the sub-graph's audio loop. */
    void processDspToIndex(float blockIndex);
    
    /**  */
    void process(float *inputBuffers, float *outputBuffers);
  
    const char *getObjectLabel();
  
    ConnectionType getConnectionType(int outletIndex);
  
    bool doesProcessAudio();
    
    /** Turn the audio processing of this graph on or off. */
    void setSwitch(bool switched);
  
    /** Returns <code>true</code> if the audio processing of this graph is turned on. <code>false</code> otherwise. */
    bool isSwitchedOn();
    
    /** Set the current block size of this subgraph. */
    void setBlockSize(int blockSize);
    
    /** Get the current block size of this subgraph. */
    int getBlockSize();
    
    /** Returns <code>true</code> of this graph has no parents, code>false</code> otherwise. */
    bool isRootGraph();
    
    /** Prints the given message to error output. */
    void printErr(char *msg);
    void printErr(const char *msg, ...);
    
    /** Prints the given message to standard output. */
    void printStd(char *msg);
    void printStd(const char *msg, ...);
    
    /** Get the argument list in the form of a <code>PdMessage</code> from the graph. */
    PdMessage *getArguments();
    
    /** Returns the global sample rate. */
    float getSampleRate();
  
    /** Returns the global dsp buffer at the given inlet. Exclusively used by <code>DspAdc</code>. */
    float *getGlobalDspBufferAtInlet(int inletIndex);
  
    /** Returns the global dsp buffer at the given outlet. Exclusively used by <code>DspDac</code>. */
    float *getGlobalDspBufferAtOutlet(int outletIndex);
  
    /** Returns the timestamp of the beginning of the current block. */
    double getBlockStartTimestamp();
  
    /** Returns the duration in milliseconds of one block. */
    double getBlockDuration();
  
    int getNumInputChannels();
    int getNumOutputChannels();
  
    /** (Re-)Computes the tree and node processing ordering for dsp nodes. */
    void computeDspProcessOrder();
  
    /**
     * Sends the given message to all [receive] objects with the given <code>name</code>.
     * This function is used by message boxes to send messages described be the syntax:
     * ;
     * name message;
     */
    void dispatchMessageToNamedReceivers(char *name, PdMessage *message);
  
    /**
     * Schedules a message to be sent to all receivers at the start of the next block.
     * @returns The <code>PdMessage</code> which will be send. It is intended that the programmer
     * will set the values of the message with a call to <code>setMessage()</code>.
     */
    PdMessage *scheduleExternalMessage(char *receiverName);
  
    /** Returns a list of directories which have neen delcared via a "declare" object. */
    List *getDeclareList();
  
  private:
    PdGraph(PdFileParser *fileParser, char *directory, int blockSize, int numInputChannels, 
            int numOutputChannels, float sampleRate, PdGraph *parentGraph);
  
    /** Connect the given <code>MessageObject</code>s from the given outlet to the given inlet. */
    void connect(int fromObjectIndex, int outletIndex, int toObjectIndex, int inletIndex);
    void connect(MessageObject *fromObject, int outletIndex, MessageObject *toObject, int inletIndex);
    
    /** Create a new object based on its initialisation string. */
    MessageObject *newObject(char *objectType, char *objectLabel, PdMessage *initMessage, PdGraph *graph);
  
    /** Add an object to the graph, taking care of any special object registration. */
    void addObject(MessageObject *node);
  
    /** Globally register a [receive~] object. Connect to registered [send~] objects with the same name. */
    void registerDspReceive(DspReceive *dspReceive);
    
    /** Globally register a [send~] object. Connect to registered [receive~] objects with the same name. */
    void registerDspSend(DspSend *dspSend);
  
    /** Returns the named global <code>DspSend</code> object. */
    DspSend *getDspSend(char *name);
  
    /** Returns the named global <code>DspCatch</code> object. */
    DspCatch *getDspCatch(char *name);
  
    /**
     * Globally register a [delwrite~] object. Registration is necessary such that they can
     * be connected to [delread~] and [vd~] objects as are they are added to the graph.
     */
    void registerDelayline(DspDelayWrite *delayline);
  
    /** Returns the named global <code>DspDelayWrite</code> object. */
    DspDelayWrite *getDelayline(char *name);
  
    /**
     * Globally register a [delread~] or [vd~] object. Registration is necessary such that they can
     * be connected to [delwrite~] objects are they are added to the graph.
     */
    void registerDelayReceiver(DelayReceiver *delayReceiver);
  
    void registerDspThrow(DspThrow *dspThrow);
  
    void registerDspCatch(DspCatch *dspCatch);
  
    /** The unique id for this subgraph. Defines "$0". */
    int graphId;
  
    /** Keeps track of the current global graph id. */
    static int globalGraphId;
  
    /** The list of arguments to the graph. Stored as a <code>PdMessage</code> for simplicity. */
    PdMessage *graphArguments;
    
    /** The number of audio input channels. */
    int numInputChannels;
    
    /** The number of audio output channels. */
    int numOutputChannels;
    
    /** True if the graph is switch on and should process audio. False otherwise. */
    bool switched;
    
    /** The parent graph. NULL if this graph is the root. */
    PdGraph *parentGraph;
    
    /** The global sample rate. */
    float sampleRate;
    
    /** The DSP block size of this graph. */
    int blockSize;
    
    /** A list of <i>all</i> <code>PdNode</code>s in this subgraph.  */
    List *nodeList;
  
    /** A list of all inlet (message or audio) nodes in this subgraph. */
    List *inletList;
    
    /** A list of all outlet (message or audio) nodes in this subgraph. */
    List *outletList;
  
    /** A global list of all [send~] objects. */
    List *dspSendList;
  
    /** A global list of all [receive~] objects. */
    List *dspReceiveList;
  
    /** A global list of all [delwite~] objects. */
    List *delaylineList;
  
    /** A global list of all [delread~] and [vd~] objects. */
    List *delayReceiverList;
  
    /** A global list of all [throw~] objects. */
    List *throwList;
  
    /** A global list of all [catch~] objects. */
    List *catchList;
  
    /** A global list of all declared directories (-path and -stdpath) */
    List *declareList;
  
    /**
     * The global <code>MessageSendController</code> which dispatches messages to named
     * <code>MessageReceive</code>ers.
     */
    MessageSendController *sendController;
    
    /**
     * A list of all <code>DspObject</code>s in this graph, in the order in which they should be
     * called in the <code>processDsp()</code> loop.
     */
    List *dspNodeList;
  
    /** A message queue keeping track of all scheduled messages. */
    OrderedMessageQueue *messageCallbackQueue;
  
    /** The start of the current block in milliseconds. */
    double blockStartTimestamp;
  
    /** The duration of one block in milliseconds. */
    double blockDurationMs;
  
    /** The registered callback function for sending data outside of the graph. */
    void (*callbackFunction)(ZGCallbackFunction, void *, void *);
  
    /** User-provided data associated with the callback function. */
    void *callbackUserData;
  
    int numBytesInInputBuffers;
    int numBytesInOutputBuffers;
  
    float *globalDspInputBuffers;
    float *globalDspOutputBuffers;
};

#endif // _PD_GRAPH_H_
