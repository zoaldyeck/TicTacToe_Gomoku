//status.h -- Indicating return status and index.
//
//wustl key: jinjinqin  chengzhen t.yin
//
//2016.3.29
#ifndef STATUS_H
#define STATUS_H
#include "stdafx.h"
//all the status
enum indicator{
	success_game, invalid_argc_number, quit_game, extract_x_failure, extract_y_failure, success_extract_x_y,
	success_move, failure_move, draw_game, unexpected_failure, second_input_wrong, null_ptr
};

enum index{ program_index, game_index };
enum argc_num {valid_argc = 2};



#endif