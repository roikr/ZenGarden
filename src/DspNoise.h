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

#ifndef _DSP_NOISE_H_
#define _DSP_NOISE_H_

#include "DspObject.h"
#include "MersenneTwister.h"

class PdGraph;

/** [noise~] */
class DspNoise : public DspObject {
    
  public:
    DspNoise(PdGraph *graph);
    ~DspNoise();
  
    const char *getObjectLabel();
    
  protected:
    void processDspToIndex(float newBlockIndex);
  
  private:
    MTRand *twister;
};

#endif // _DSP_NOISE_H_
