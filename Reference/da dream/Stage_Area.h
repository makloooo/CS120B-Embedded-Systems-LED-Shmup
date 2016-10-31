#ifndef STAGE_AREA_H_
#define STAGE_AREA_H_

#define SEGMENT_LEN	8
#define STG_WIDTH	32
#define STG_HEIGHT	32

#define DATA_W		STG_WIDTH/SEGMENT_LEN
#define DATA_H		STG_HEIGHT

#include "Arduino.h"

class StageArea {
	private:
		byte matrix_data[DATA_H][DATA_W];
	public:
		StageArea();
		
		void clearMatrix();
		
		void placePixel(byte x, byte y);
		void placeLine(byte x0, byte y0, byte x1, byte y1);
		void placeCircle(byte x0, byte y0, byte r);

		byte getSegment(byte r, byte c);
		void writeSegment(byte r, byte c, byte seq);
};

#endif /* STAGE_AREA_H_ */