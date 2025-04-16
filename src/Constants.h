#pragma once

//const char* WINDOW_NAME = "Billard 51";

//Game general information
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768 

#define BALL_SPRITE_SIZE 256
#define TABLE_SPRITE_WSIZE 767
#define TABLE_SPRITE_HSIZE 414
#define POCKET_SPRITE_SIZE 45


#define BALL_SIZE 24
#define BALL_RADIUS 12
#define TABLE_WSIZE 767
#define TABLE_HSIZE 414
#define POCKET_SIZE 30
#define POCKET_RADIUS 30

#define BALL_STEPS 150
#define TABLE_MARGINS 44
#define NUM_BALLS 16
#define NUM_POCKETS 6

#define STOP_THRESHOLD 0.01f

#define UNIT_SIZE 48
#define COLOR_WHITE {255, 255, 255, 255}
#define COLOR_BLACK {0, 0, 0, 255}
#define COLOR_RED {255, 0, 0, 255}
#define COLOR_GREEN {0, 255, 0, 255}
#define COLOR_BLUE {0, 0, 255, 255}

const std::string TXT_HITS_P1 = "P1 HITS:";
const std::string TXT_HITS_P2 = "P2 HITS:";



//--------------TEXTURE RECT ID'S--------------
const std::string TABLE_ID = "Table";
const std::string BALLS_ID = "Balls";
const std::string POCKET_ID = "Pocket";

const std::string TXT_ID_HITS_P1 = "Score1";
const std::string TXT_ID_HITS_P2 = "Score2";
const std::string TXT_ID_SCORE_PL1 = "ScoreP1";
const std::string TXT_ID_SCORE_PL1_ACTIVE = "ScoreP1_Active";
const std::string TXT_ID_SCORE_PL1_INACTIVE = "ScoreP1_Inactive";
const std::string TXT_ID_SCORE_PL2 = "ScoreP2";
const std::string TXT_ID_SCORE_PL2_ACTIVE = "ScoreP2_Active";
const std::string TXT_ID_SCORE_PL2_INACTIVE = "ScoreP2_Inactive";
const std::string TTF_ID_GAMEOVER = "GameOver";

const std::string BT_ID_PLAY = "PlayButton";
const std::string BT_ID_PLAY_N = "PlayButton_Normal";
const std::string BT_ID_PLAY_H = "PlayButton_Hover";

const std::string TXT_ID_AUDIO = "Audio";

const std::string BT_ID_LEFT_AUDIO = "LeftAudio";
const std::string BT_ID_LEFT_AUDIO_N = "LeftAudio_Normal";
const std::string BT_ID_LEFT_AUDIO_H = "LeftAudio_Hover";
const std::string BT_ID_RIGHT_AUDIO = "RightAudio";
const std::string BT_ID_RIGHT_AUDIO_N = "RightAudio_Normal";
const std::string BT_ID_RIGHT_AUDIO_H = "RightAudio_Hover";

const std::string BT_ID_ONOFF_AUDIO = "OnOffAudio";
const std::string BT_ID_ON_AUDIO_N = "OnAudio_N";
const std::string BT_ID_ON_AUDIO_H = "OnAudio_H";
const std::string BT_ID_OFF_AUDIO_N = "OffAudio_N";
const std::string BT_ID_OFF_AUDIO_H = "OffAudio_H";

const std::string TXT_ID_AUDIO_VALUE = "AudioValue";

const std::string BT_ID_DELETE_RANK = "DeleteRanking";
const std::string BT_ID_DELETE_RANK_N = "DeleteRanking_Normal";
const std::string BT_ID_DELETE_RANK_H = "DeleteRanking_Hover";

const std::string BT_ID_EXIT = "ExitButton";
const std::string BT_ID_EXIT_N = "ExitButton_Normal";
const std::string BT_ID_EXIT_H = "ExitButton_Hover";

const std::string BT_ID_RESTART = "RestartButton";
const std::string BT_ID_RESTART_N = "RestartButton_Normal";
const std::string BT_ID_RESTART_H = "RestartButton_Hover";

const std::string TXT_ID_PLAYING_STRIPES = "PlayingStripes";
const std::string TXT_ID_PLAYING_STRIPES_ACTIVE = "PlayingStripes_Active";
const std::string TXT_ID_PLAYING_STRIPES_INACTIVE = "PlayingStripes_Inactive";

const std::string TXT_ID_PLAYING_SOLIDS = "PlayingSolids";
const std::string TXT_ID_PLAYING_SOLIDS_ACTIVE = "PlayingSolids_Active";
const std::string TXT_ID_PLAYING_SOLIDS_INACTIVE = "PlayingSolids_Inactive";

const std::string TXT_ID_INSERT_NAME = "InsertName";
const std::string TXT_ID_INPUT_NAME = "InputName";

const std::string BT_ID_SAVE_RANKING = "SaveRanking";
const std::string BT_ID_SAVE_RANKING_N = "SaveRanking_N";
const std::string BT_ID_SAVE_RANKING_H = "SaveRanking_H";

const std::string TXT_ID_RANKING_SCORES = "RankingScores";



//--------------RESOURCE PATH--------------
//Textures
const std::string TABLE_PATH = "../res/img/table.png";
const std::string BALLS_PATH = "../res/img/balls.png";
const std::string POCKET_PATH = "../res/img/pocket.png";

//Fonts
const std::string GAMEOVER_FONT_PATH = "../res/ttf/game_over.ttf";

const std::string RANKING_PATH = "../res/files/ranking.bin";

const std::string MENU_MUSIC_PATH = "../res/au/menu.mp3";
const std::string GAME_MUSIC_PATH = "../res/au/game_theme.mp3";


