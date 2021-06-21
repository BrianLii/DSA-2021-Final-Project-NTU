#include "api.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define SWAP(a,b,type) {type tmp=a;a=b;b=tmp;}
#define TOK 1
#define OPR 2
#define isop(c) (c=='('||c==')'||c=='&'||c=='!'||c=='|')
#define isch(c) (('0'<=c&&c<='9')||('a'<=c&&c<='z'))
int n_mails,n_queries;
mail *mails;
query *queries;
typedef struct node
{
	int type,data;
}node;
typedef long long ll;
inline int chrtoi(char c);
int chrtoi(char c)
{
	if('a'<=c&&c<='z')return c-'a';
	if('A'<=c&&c<='Z')return 26+c-'A';
	else return 52+c-'0';
}
INIT_sim_s
double similar[10000][10000];
int token_set_size[10000]={90,76,281,641,68,85,146,882,264,86,362,25,113,45,316,24,22,25,86,126,91,12,80,59,44,55,130,171,44,769,24,19,219,114,734,31,277,25,202,13,37,235,12,39,47,36,89,181,273,16,343,135,289,12,99,40,191,124,35,86,67,503,154,98,28,40,1387,350,99,229,156,28,43,82,40,60,57,286,276,95,13,18,105,90,32,41,205,96,20,285,48,557,93,104,371,40,35,27,54,19,25,23,286,270,71,51,26,595,36,282,39,58,178,29,108,138,240,268,28,37,70,20,162,58,250,36,118,27,449,232,304,105,19,45,604,64,28,311,118,232,143,62,31,181,213,13,33,298,242,41,115,209,96,132,452,367,849,106,481,24,32,42,81,46,25,174,40,103,46,138,241,39,298,268,21,57,365,857,136,55,31,51,42,59,67,53,368,185,46,119,527,47,42,38,49,32,385,69,116,74,13,389,117,275,70,199,41,448,94,432,283,299,48,431,305,123,37,11,23,272,208,32,58,63,13,482,161,226,1175,319,14,127,71,12,154,83,104,356,183,96,27,88,56,92,68,79,1246,76,84,73,80,119,186,12,324,31,37,18,68,203,343,33,247,81,481,61,53,149,157,64,17,147,137,123,82,24,63,125,23,155,14,60,175,31,65,194,195,18,226,21,86,725,101,177,358,98,63,111,93,17,1253,122,164,194,88,378,110,40,290,34,114,9,104,76,30,123,39,13,57,439,122,177,75,835,55,78,68,33,39,131,39,76,559,183,397,693,31,180,22,300,14,214,442,1317,154,52,29,411,171,339,572,81,180,181,106,16,296,77,47,1183,1217,253,66,12,65,128,282,346,47,22,12,43,46,88,164,12,18,44,234,186,153,1043,704,29,70,213,43,253,50,92,29,185,211,19,13,833,435,72,404,286,129,25,57,228,17,46,197,62,99,37,248,530,133,55,83,64,102,47,82,66,40,62,94,28,201,94,173,47,108,89,194,29,885,484,47,55,136,104,205,83,93,115,26,243,257,269,39,59,56,16,57,136,40,187,218,213,413,48,68,54,1123,96,147,109,47,18,197,88,151,141,27,185,46,71,103,75,67,28,54,72,106,497,132,129,108,14,48,144,829,66,24,158,247,91,791,43,368,112,455,23,40,49,19,29,507,68,415,12,13,168,20,50,16,32,214,143,34,97,88,252,61,72,122,59,26,26,125,179,35,62,270,39,220,56,36,160,238,212,22,484,32,37,24,43,13,56,101,24,93,93,758,24,154,51,82,64,347,53,47,74,281,599,65,188,195,295,165,436,93,25,23,46,103,16,118,28,25,45,699,26,33,110,99,272,13,12,38,258,94,25,33,42,53,50,91,234,28,301,97,14,439,93,160,111,515,256,247,82,12,545,82,191,526,298,59,59,128,289,24,31,61,41,28,72,131,19,48,23,39,50,157,45,102,129,16,18,95,85,23,82,1460,391,142,302,35,64,203,121,60,429,500,63,158,44,219,171,183,122,259,134,65,24,33,50,47,42,40,25,14,60,553,371,279,70,149,11,226,61,161,46,121,43,388,29,224,120,189,668,82,231,33,57,13,117,188,116,169,54,43,184,94,229,308,73,35,90,353,387,88,34,100,54,59,62,174,451,60,28,375,170,41,104,263,76,36,38,186,42,51,160,199,55,25,694,28,29,20,997,45,110,30,30,747,127,30,170,345,405,19,53,257,104,27,72,50,46,20,24,51,21,209,52,221,52,14,29,27,153,628,36,59,207,21,32,16,116,224,191,139,431,206,383,188,85,425,317,536,19,29,426,104,267,65,52,244,371,365,152,14,25,12,228,13,44,56,57,307,413,218,302,88,284,161,165,85,113,12,109,20,27,59,155,20,14,2174,26,138,58,41,12,31,104,17,127,132,205,244,102,14,154,58,43,184,53,111,210,320,634,1356,678,1581,232,23,52,141,41,86,475,783,30,98,211,158,406,164,153,150,105,150,41,49,48,420,201,40,269,25,47,285,233,140,44,174,312,196,174,299,15,190,48,70,68,1033,376,187,38,362,186,56,215,13,138,180,47,104,65,323,662,71,346,106,42,321,84,44,206,352,150,92,32,256,148,61,151,65,123,63,140,340,79,23,69,28,259,28,74,132,25,77,130,28,21,17,257,46,109,161,28,43,19,342,15,24,223,437,113,35,16,138,83,13,407,93,101,27,329,154,28,20,50,334,82,107,181,212,106,29,414,151,49,236,51,47,238,158,57,175,212,18,73,215,20,149,36,12,69,70,220,20,305,130,101,102,218,89,37,105,24,68,51,465,53,142,161,161,87,32,57,1011,32,64,332,591,27,137,33,21,185,278,525,90,90,468,229,18,724,325,368,191,53,122,24,103,129,425,191,299,690,33,179,28,38,49,294,125,34,171,104,34,74,413,642,47,140,100,104,68,99,111,614,40,41,30,43,74,183,117,35,128,48,261,88,58,41,132,91,13,142,52,167,12,25,325,596,229,550,60,81,127,229,219,49,117,467,167,87,85,53,133,17,189,20,183,43,33,57,459,26,12,41,93,310,29,75,223,559,248,29,205,120,79,249,43,41,38,408,49,31,113,75,41,83,15,23,104,14,30,110,107,272,35,94,200,257,249,430,324,400,104,205,252,281,268,210,321,123,81,13,21,14,22,148,95,9,149,349,337,89,53,197,88,21,299,416,50,162,80,54,49,29,36,175,57,786,1783,70,1249,37,537,20,22,163,318,41,44,78,114,118,122,93,63,147,103,150,116,367,572,360,221,313,13,126,58,31,57,191,173,1267,146,244,11,258,189,41,73,219,22,174,39,83,19,456,206,60,65,293,246,88,221,52,196,135,252,71,437,65,39,21,1577,38,71,55,143,330,705,262,79,34,237,341,67,12,12,65,45,13,462,77,104,131,74,154,209,32,140,67,707,337,12,278,22,395,210,143,192,56,45,33,303,63,155,340,12,57,102,93,172,87,148,294,241,18,280,401,334,70,50,36,17,157,35,51,42,154,75,240,51,105,28,12,85,96,13,14,279,377,278,34,47,65,283,230,51,84,355,20,44,472,47,44,82,115,100,94,29,55,29,224,55,41,354,22,93,187,25,131,108,35,52,46,41,115,180,214,13,754,13,22,74,84,113,58,13,119,206,41,13,41,124,16,96,16,41,295,31,86,45,82,84,464,54,188,28,331,115,194,81,42,13,256,455,314,319,233,94,33,47,191,33,382,464,101,52,128,11,209,308,182,403,135,358,50,16,234,58,156,18,171,246,1096,78,186,24,285,351,536,115,141,57,293,60,378,624,136,27,17,321,35,27,219,362,108,63,210,55,213,71,88,131,166,63,218,284,525,179,92,83,54,258,84,77,324,90,38,26,165,60,89,17,21,138,87,31,580,52,164,67,107,101,65,305,35,57,130,833,117,18,1466,89,21,225,18,13,23,103,32,82,814,113,842,81,91,258,13,356,15,58,13,767,76,620,210,887,24,21,240,96,58,93,68,1193,159,25,160,184,336,60,52,85,129,64,342,42,101,52,32,358,317,157,572,118,15,324,25,34,52,120,572,256,22,481,345,121,287,250,51,179,53,185,262,325,46,13,50,15,62,153,14,197,17,216,23,44,38,75,28,105,308,177,54,110,36,149,33,13,33,60,87,34,314,118,67,286,30,132,45,28,13,40,13,42,59,75,114,44,41,84,395,186,321,114,44,82,80,60,68,14,43,63,38,554,729,987,59,138,42,12,27,213,130,315,23,80,110,785,126,56,201,79,31,24,108,105,273,69,52,98,32,173,172,45,208,106,159,37,254,167,22,134,105,104,17,387,126,31,412,25,225,27,38,75,789,84,65,54,36,15,108,375,29,52,34,12,27,173,133,75,14,312,12,152,44,235,694,14,90,108,53,29,26,41,70,90,173,27,124,230,26,201,92,88,20,44,599,473,225,64,83,43,177,187,412,158,52,222,74,169,116,80,61,254,343,276,24,119,110,12,353,78,71,1213,50,64,606,352,13,125,83,338,260,51,120,20,316,22,245,38,248,37,38,17,312,12,14,106,1481,61,331,25,32,133,191,28,254,17,12,17,50,28,14,77,152,59,53,228,64,55,30,45,51,308,247,36,383,73,38,62,41,120,85,27,215,81,323,42,99,51,526,58,177,29,201,28,90,185,184,52,19,44,159,769,57,201,231,44,143,151,34,131,309,80,68,99,18,34,30,57,123,12,236,128,127,29,54,57,334,1050,102,90,41,65,67,101,52,38,34,33,69,115,548,77,41,588,226,40,245,351,96,493,19,63,216,54,35,200,54,35,30,89,21,28,39,384,115,132,123,58,202,25,38,68,52,268,32,185,252,810,113,13,267,324,77,55,23,17,64,89,124,27,168,95,29,13,53,32,127,443,119,29,44,120,13,61,70,91,55,67,203,51,514,123,65,125,199,105,193,110,361,53,22,20,152,70,219,402,62,143,311,41,184,12,22,16,98,109,28,148,506,41,108,1120,339,343,133,50,377,1269,75,259,30,147,63,150,13,31,174,65,42,99,138,502,39,88,76,44,106,67,13,520,51,56,1531,130,12,295,119,61,64,1090,18,50,40,47,45,551,34,52,41,100,77,12,31,44,70,80,74,147,31,34,180,184,118,31,168,270,76,42,37,200,728,562,109,101,114,29,147,194,398,20,497,295,1282,649,87,60,380,242,11,376,32,213,29,2155,304,26,14,1197,25,901,113,411,143,92,39,34,447,208,60,742,32,38,73,105,313,266,59,92,121,137,165,43,175,17,29,51,51,73,25,57,12,187,130,102,219,51,410,131,13,79,254,91,237,32,839,138,57,25,63,73,76,47,100,111,30,51,136,133,40,51,185,136,194,26,96,21,1249,958,88,352,169,498,136,355,448,236,123,59,42,35,118,28,47,253,78,28,75,613,31,62,342,117,453,198,91,19,806,159,106,17,205,13,54,92,119,33,34,187,118,33,100,27,25,79,12,283,303,25,165,133,142,20,236,19,22,61,61,111,39,30,52,48,79,260,221,31,44,440,570,144,215,91,41,158,94,36,772,27,169,13,344,31,130,33,89,854,27,131,48,23,71,270,63,259,202,19,63,411,103,203,20,53,28,107,85,1630,687,62,20,70,120,394,135,61,35,28,167,283,13,100,133,56,131,198,187,27,52,52,46,13,168,103,222,175,119,118,35,536,432,181,238,13,216,64,337,33,12,26,69,112,92,462,50,214,467,496,109,41,71,13,112,128,36,132,49,36,143,31,320,56,176,265,52,92,119,73,373,355,145,32,136,271,263,34,30,165,157,13,24,208,87,72,220,306,267,19,123,101,193,81,571,207,20,18,846,296,113,104,15,119,198,20,387,147,127,694,151,455,13,38,207,114,263,28,20,520,123,227,46,228,528,671,12,87,44,124,75,383,217,41,85,562,673,526,71,281,48,34,51,156,22,37,194,68,255,82,361,124,90,143,517,190,56,60,362,76,136,69,30,136,132,67,251,10,39,139,268,37,960,630,22,259,21,27,22,38,65,52,312,28,114,261,17,97,105,48,138,100,34,70,234,30,193,128,132,62,16,13,100,52,227,178,132,33,54,59,21,32,38,58,350,116,174,51,194,77,149,968,135,161,207,595,150,196,313,34,187,254,38,75,49,401,51,230,170,123,320,52,167,32,58,140,12,75,40,146,408,23,61,506,12,114,189,88,28,103,199,144,32,113,32,183,33,59,216,44,205,119,38,23,259,21,117,60,23,18,34,329,87,100,48,40,57,145,85,118,114,57,84,84,28,107,43,20,551,147,222,18,370,158,338,275,74,304,25,125,19,629,295,187,52,70,186,1669,29,200,84,17,433,467,36,56,13,55,38,61,72,14,654,227,103,19,61,69,334,26,204,51,247,1652,44,205,42,44,21,23,270,111,120,581,18,68,85,178,136,22,112,85,111,102,12,259,27,176,39,25,59,149,165,46,100,319,261,101,389,44,13,55,96,154,41,359,125,103,37,82,337,302,14,12,251,170,62,674,95,59,61,185,12,23,167,39,459,137,201,164,176,80,27,30,59,79,239,218,40,150,355,469,206,47,110,39,19,173,86,69,65,40,168,23,95,549,29,173,279,585,131,14,90,42,50,115,70,141,86,175,18,42,169,146,453,192,73,625,29,341,209,51,154,116,172,238,32,51,130,331,1102,55,43,31,13,432,39,247,13,33,2800,124,479,208,147,36,372,141,42,232,100,13,177,13,460,24,509,260,13,833,601,192,222,262,75,54,67,29,218,41,77,22,241,809,37,238,27,41,217,51,63,99,68,70,39,91,15,219,64,159,18,92,18,164,112,95,81,83,20,79,26,38,67,66,180,21,1162,153,66,1117,14,94,277,111,187,341,227,227,142,35,49,153,1076,241,835,487,336,314,483,885,37,20,352,107,245,51,20,25,41,75,197,42,113,197,18,772,77,486,37,40,267,27,57,87,14,35,66,312,84,100,96,58,27,362,12,21,134,75,203,286,32,249,29,72,63,27,81,175,80,15,104,870,20,73,128,19,58,120,139,61,52,110,129,28,1001,23,52,80,38,517,85,23,53,381,104,154,27,86,142,144,129,548,96,154,174,76,181,98,214,188,244,116,437,219,69,379,34,437,47,57,68,458,37,480,13,188,44,358,144,101,229,21,230,41,342,1379,57,237,160,312,52,101,286,26,20,127,364,155,173,35,128,219,23,834,205,122,415,20,29,24,156,200,151,120,41,205,148,268,198,602,224,180,177,37,393,36,69,228,143,54,191,84,30,48,36,386,80,126,89,50,245,188,41,143,241,72,1106,78,19,188,51,237,148,330,60,199,25,350,19,37,104,13,390,277,86,139,162,192,67,12,521,258,649,153,200,85,168,74,12,21,129,24,76,36,328,77,19,47,35,37,128,32,61,64,67,96,48,56,27,150,35,101,50,34,100,357,251,63,344,117,346,29,141,262,51,147,50,67,15,56,915,79,59,47,36,85,43,61,99,74,151,35,17,94,322,59,337,260,279,415,161,15,13,57,33,180,36,173,494,60,195,29,383,27,413,92,26,13,979,96,21,26,52,179,147,45,42,187,156,34,291,211,85,74,351,69,352,332,127,65,66,212,19,22,100,252,140,87,246,217,358,41,36,270,15,54,27,182,1256,255,124,147,143,410,49,108,74,353,17,35,432,13,188,254,179,61,322,225,56,62,305,47,155,40,594,738,38,90,122,64,63,35,29,32,249,51,66,187,69,201,84,93,209,80,307,253,650,70,185,37,42,13,43,227,66,56,29,29,590,24,150,95,223,68,1065,421,145,32,281,112,52,38,92,30,294,161,34,28,225,89,17,23,138,52,101,89,475,465,59,102,63,72,63,262,32,37,454,54,61,17,193,16,82,27,82,66,21,131,53,161,35,16,224,756,143,160,134,217,290,165,64,40,62,42,108,78,139,36,95,47,647,24,60,86,229,121,187,160,135,576,208,185,18,124,227,410,73,12,143,362,35,21,137,120,129,221,37,55,202,146,155,305,132,33,92,531,131,398,54,31,39,397,396,166,242,227,22,42,52,92,629,107,76,938,89,133,28,587,54,474,170,237,32,507,121,68,87,111,189,83,81,160,29,347,61,484,64,124,53,177,43,149,19,26,181,237,15,460,12,17,166,106,491,101,213,323,99,119,123,61,31,132,109,20,15,764,915,35,424,39,13,24,81,18,313,138,903,47,148,102,153,160,27,212,235,66,169,981,49,28,228,20,21,18,68,80,165,13,80,26,18,269,211,258,18,163,110,88,47,44,72,238,108,218,50,133,78,88,112,28,75,20,38,131,80,151,145,117,30,1039,127,192,48,918,24,61,35,377,12,59,42,31,249,352,123,17,21,26,207,114,29,98,156,53,53,440,149,53,57,95,25,52,109,183,19,50,91,26,237,177,872,282,107,249,126,120,267,30,138,97,39,168,325,174,511,73,473,85,283,92,25,76,12,104,776,63,93,74,37,74,100,582,101,88,25,1307,144,207,72,312,46,22,659,405,63,174,67,239,1288,210,130,182,101,124,404,170,37,18,27,276,38,186,163,739,118,1572,13,29,176,71,251,621,172,426,37,32,160,95,65,145,186,1203,528,29,54,98,140,40,137,121,19,151,173,15,97,34,91,118,90,14,12,96,281,219,131,25,49,36,13,41,56,173,34,32,50,307,160,79,54,1191,83,28,120,61,187,150,201,166,44,70,92,166,664,161,113,72,383,75,66,30,66,58,43,30,159,12,188,28,36,29,64,26,36,54,81,99,306,333,71,94,211,69,360,116,465,499,521,134,406,199,23,1313,208,185,277,104,198,51,178,402,121,283,193,208,112,17,135,34,93,76,70,20,104,185,52,258,56,99,15,75,219,52,19,145,116,22,14,82,125,201,31,12,167,94,380,13,86,682,150,343,20,520,243,212,13,190,32,54,32,153,117,486,31,87,337,539,51,77,14,182,213,683,49,23,211,118,239,30,25,348,43,546,99,349,71,134,42,372,101,323,58,315,172,737,37,259,19,230,63,31,60,243,24,264,12,28,820,67,55,73,298,208,64,76,16,284,1139,49,177,34,16,914,68,23,23,20,14,21,63,49,207,68,127,27,352,278,364,110,58,44,97,12,14,238,70,135,69,595,25,1065,132,156,435,99,506,96,311,130,1431,17,37,112,64,25,126,437,48,39,486,64,627,25,26,163,517,130,599,39,39,63,120,54,34,75,165,20,28,36,1110,163,206,245,41,407,71,218,80,20,147,124,41,138,61,26,38,68,96,74,292,64,21,28,106,20,48,541,123,75,843,20,43,111,24,1043,51,71,32,115,162,196,104,38,21,355,47,24,93,28,96,489,561,79,204,51,104,70,160,440,32,328,30,103,17,191,95,144,68,120,568,362,14,176,647,42,13,25,35,786,128,519,19,159,166,58,456,622,626,13,21,300,58,103,25,334,22,221,90,36,99,450,40,88,262,142,29,296,45,106,56,226,216,31,61,124,138,76,198,17,144,224,96,293,128,654,23,313,161,26,107,21,19,426,359,42,393,264,31,29,66,17,219,37,71,78,558,52,62,16,177,71,16,168,42,13,33,39,112,208,122,17,77,38,133,317,14,342,94,72,86,20,59,328,118,70,77,29,190,13,47,49,341,3213,81,57,41,33,155,33,53,37,415,56,525,289,64,24,187,65,28,398,22,68,341,66,87,51,154,14,34,36,159,509,50,80,34,271,62,70,301,326,167,58,97,17,12,136,34,39,17,110,197,91,23,663,150,630,149,147,260,290,58,284,205,54,141,46,158,17,20,49,280,13,100,261,70,27,13,12,104,50,207,453,268,95,119,108,30,486,226,31,424,453,262,81,21,12,37,247,19,206,327,24,862,37,43,118,288,53,81,63,122,40,99,41,103,180,141,137,34,129,151,446,160,71,79,63,1006,14,413,127,167,88,85,1288,17,15,25,49,212,18,188,115,104,80,44,145,28,548,24,21,76,156,143,137,145,71,25,27,46,102,32,68,529,142,25,62,126,13,76,54,13,159,315,12,24,129,65,76,476,211,129,52,28,35,33,166,34,55,28,144,286,124,201,402,135,158,54,55,31,419,1142,39,469,544,15,231,22,35,101,32,27,106,58,343,18,97,162,44,51,105,208,346,263,20,119,140,304,209,109,56,175,40,435,61,106,68,163,38,90,218,37,81,16,69,153,74,38,53,96,30,370,64,53,301,60,172,232,235,462,115,175,240,126,17,114,27,72,197,17,118,51,28,68,129,86,35,48,538,437,44,43,101,168,278,60,399,23,619,51,17,13,62,49,93,972,157,72,326,289,60,117,54,225,305,446,198,52,58,147,50,390,333,57,46,272,110,148,64,180,33,20,87,265,37,45,67,106,22,528,63,29,23,98,1139,1297,850,14,131,87,390,78,60,209,12,36,71,35,201,222,180,129,131,200,66,398,216,19,18,157,92,214,46,106,186,1713,42,137,14,126,98,12,86,190,203,24,130,26,47,196,64,73,105,63,63,41,19,105,284,21,110,984,229,38,71,23,51,349,210,303,133,192,25,162,822,27,64,313,1426,104,202,243,393,27,302,70,557,18,65,317,187,139,62,114,137,114,43,117,35,197,22,67,54,97,59,264,33,227,243,70,83,32,108,85,99,26,72,12,244,60,47,19,34,108,298,13,35,62,74,139,83,137,36,416,88,86,77,40,88,44,369,47,24,65,72,18,68,117,83,80,35,62,83,80,43,469,63,18,245,82,43,43,1186,46,72,66,13,90,12,40,530,73,153,141,13,128,158,106,95,158,264,23,68,734,86,706,19,133,104,20,9,34,14,102,113,399,13,69,35,54,50,80,21,79,21,44,231,442,258,27,184,94,144,32,24,52,72,285,34,30,72,12,19,159,235,350,23,84,41,45,22,256,188,141,82,36,180,67,90,86,91,135,27,131,202,33,71,34,423,57,65,67,35,196,298,28,212,19,265,284,36,64,15,52,30,138,225,231,83,358,83,134,56,130,116,137,49,374,17,113,134,1035,31,424,212,143,52,733,17,127,241,689,141,150,234,50,105,1379,24,13,15,96,21,74,58,85,16,37,269,15,22,215,223,97,41,113,12,1680,75,125,198,297,15,29,28,102,15,53,124,373,120,57,86,324,57,176,79,94,144,52,583,118,1771,112,54,554,82,38,576,708,19,200,348,41,108,64,16,32,43,40,150,431,19,86,18,158,74,38,185,21,57,46,12,1294,422,16,43,43,244,17,16,96,25,18,62,482,382,109,83,13,112,215,126,13,88,35,47,74,82,37,27,31,70,490,343,86,181,36,44,266,35,32,29,147,27,46,104,43,62,657,72,111,284,80,323,262,183,375,77,78,13,59,20,264,13,212,216,400,367,47,161,13,66,46,88,330,61,24,80,65,276,60,164,61,76,169,154,345,157,28,48,383,37,114,24,161,234,16,441,74,38,63,299,41,101,2174,16,14,215,75,649,152,257,54,252,141,52,19,91,60,52,383,69,243,687,29,489,43,51,21,179,48,215,819,470,371,60,41,24,37,29,129,351,130,54,51,302,181,234,42,15,246,71,29,267,21,121,476,67,106,698,328,53,113,496,110,203,49,83,49,823,24,123,52,42,63,441,253,176,27,86,17,65,544,302,76,94,38,52,466,81,272,17,26,272,122,161,91,111,204,61,94,50,37,105,95,15,82,12,335,111,25,187,91,65,55,51,166,37,34,22,203,56,111,634,29,73,511,957,47,45,69,20,132,196,493,259,114,79,36,96,58,233,22,97,12,49,221,151,71,52,82,12,146,92,95,54,123,342,380,103,12,206,12,87,202,283,28,90,72,14,216,45,34,29,17,37,96,28,16,54,175,30,85,85,130,916,18,655,151,69,79,65,773,28,29,230,59,164,12,47,133,14,43,41,53,341,92,181,29,444,564,234,19,56,53,117,34,164,43,208,709,12,439,20,78,29,59,30,13,26,317,152,68,44,36,95,30,488,114,371,51,12,198,414,34,367,219,208,108,67,41,30,147,245,180,55,474,139,12,50,27,402,222,154,30,132,39,485,159,185,103,132,314,101,132,16,99,41,56,12,305,83,105,76,514,510,257,91,139,34,330,142,26,32,519,17,75,279,114,24,185,872,72,38,84,1726,228,65,38,158,28,129,254,69,80,172,329,51,317,61,212,76,39,300,31,27,140,184,65,15,35,194,40,12,80,63,31,16,465,232,394,219,37,576,60,87,12,142,715,37,237,164,53,130,173,181,98,195,376,23,33,79,13,50,113,148,130,13,27,98,78,106,14,475,616,142,62,89,154,129,31,30,57,119,28,539,39,39,199,79,172,171,16,450,26,71,15,329,57,236,130,32,268,96,152,59,165,73,180,144,527,139,486,81,92,28,233,325,109,12,85,35,269,72,897,44,53,25,35,12,525,279,370,273,142,32,77,231,36,29,356,41,80,89,102,103,38,125,22,135,41,52,36,67,289,187,97,84,44,62,97,73,62,69,332,121,150,332,46,27,202,245,43,28,161,447,23,671,172,39,65,175,16,422,340,196,27,184,104,187,1003,95,93,13,55,318,27,72,94,258,66,77,19,23,13,67,565,490,72,67,96,13,1568,267,63,177,189,306,98,160,84,141,43,33,45,13,109,77,58,143,446,43,358,29,37,13,27,159,202,19,145,228,62,358,61,290,46,27,177,97,215,49,113,277,118,127,184,46,36,174,387,50,19,40,202,179,484,124,14,19,108,233,299,183,162,173,309,234,111,107,54,54,32,97,39,85,628,125,128,29,220,33,111,77,107,220,89,544,9,25,218,25,328,42,114,494,15,59,272,66,33,222,471,302,30,80,26,13,123,27,30,404,15,182,46,82,20,167,39,42,419,160,19,215,276,1056,180,152,43,118,27,215,128,82,72,479,91,105,13,430,170,55,129,29,47,15,241,503,396,12,157,45,82,32,193,55,296,27,13,71,398,64,39,387,61,29,158,75,39,17,14,88,13,188,13,99,643,79,112,127,77,473,370,180,21,54,163,30,13,316,129,219,267,32,66,16,146,139,42,93,55,42,280,277,37,145,229,115,24,377,544,235,54,28,239,116,380,23,111,135,39,76,14,23,22,500,127,135,376,391,75,34,1184,14,286,25,632,55,319,40,98,186,128,39,234,28,122,223,1641,270,39,50,36,141,16,34,621,15,300,1106,39,102,197,53,427,77,153,62,18,189,54,116,23,53,198,266,460,96,483,32,323,23,28,156,165,103,41,17,155,50,277,77,27,24,531,178,169,536,65,39,166,50,348,168,341,440,298,120,75,150,13,313,98,55,319,142,332,49,34,53,438,343,239,64,101,9,95,147,411,21,182,17,39,281,32,385,39,95,46,29,62,36,64,92,47,37,488,51,54,88,182,83,125,247,91,149,323,48,289,112,30,14,466,686,50,192,147,44,75,110,18,153,92,47,39,20,12,170,53,722,93,33,47,77,99,153,63,160,520,20,69,34,193,996,503,325,392,281,61,46,128,29,48,224,24,92,30,240,95,134,268,104,79,152,228,133,62,48,64,127,43,181,52,32,81,225,48,200,410,12,183,331,193,63,30,30,21,37,21,97,26,122,93,133,102,65,42,336,30,46,562,229,67,164,74,134,123,27,50,285,79,83,75,383,81,30,166,148,53,69,466,30,121,210,225,92,15,218,472,157,33,330,105,472,104,34,298,268,47,228,316,70,987,123,67,13,113,310,149,43,850,46,258,61,127,34,33,95,140,34,120,25,51,57,62,27,658,94,214,53,52,189,233,49,21,100,14,38,47,152,41,93,303,110,92,39,40,53,27,27,266,117,531,55,201,88,218,274,241,82,37,143,915,92,83,129,78,92,27,97,445,41,125,32,182,80,223,112,117,39,16,299,73,142,90,453,87,32,278,32,32,128,113,11,105,165,555,150,93,49,408,153,454,229,213,322,58,415,37,17,459,86,31,29,396,262,45,81,813,86,26,149,12,462,21,224,513,651,90,111,52,170,85,52,52,335,44,105,219,62,67,85,67,122,70,90,63,254,495,175,1526,17,44,124,80,278,472,20,734,112,40,41,13,160,415,17,636,12,32,13,221,56,85,39,656,39,765,334,118,152,79,59,217,291,140,20,242,26,130,171,83,432,42,108,128,741,222,40,396,212,191,51,293,96,299,127,185,53,85,162,135,109,70,156,234,91,477,77,201,170,711,45,18,34,178,26,57,56,15,23,225,703,119,17,325,95,19,130,97,112,147,241,36,178,135,163,192,293,132,191,138,12,161,18,29,52,333,30,437,335,249,97,93,12,37,296,38,20,126,61,31,81,89,163,819,46,103,399,570,43,500,96,236,276,24,13,108,162,101,59,155,115,132,65,350,37,54,152,2225,13,94,22,17,22,697,28,12,21,197,717,338,19,17,38,39,332,130,69,186,16,38,64,113,59,137,175,264,80,57,18,37,89,237,55,32,106,803,131,29,91,20,229,48,70,87,17,53,53,51,308,64,59,51,22,106,159,65,378,45,69,29,142,399,34,133,232,96,58,141,26,273,96,85,135,259,229,291,88,360,123,215,23,11,183,12,56,328,309,238,22,181,108,156,17,21,19,55,172,48,108,126,43,112,14,232,158,122,44,18,239,281,118,38,20,103,40,192,84,156,16,172,340,56,94,29,35,128,347,45,264,47,206,31,312,51,131,124,22,205,330,148,81,139,103,317,173,70,56,42,331,432,47,35,646,37,30,366,63,168,48,60,72,13,272,42,24,81,304,216,20,24,24,283,25,39,397,139,104,49,133,120,177,164,29,35,23,97,101,62,1548,238,55,92,22,189,407,114,275,223,20,267,82,82,384,448,45,138,135,54,135,678,15,401,60,15,254,83,58,104,148,344,32,17,473,134,1108,16,100,41,242,61,80,43,100,41,23,16,81,58,13,32,110,130,60,82,214,100,76,27,23,81,45,34,37,458,458,13,146,97,203,46,111,267,61,127,27,99,285,41,1587,321,88,35,25,97,133,479,95,111,82,98,13,118,116,176,37,298,25,90,34,36,187,35,259,226,52,167,68,39,58,176,235,213,141,611,200,349,31,21,32,159,39,63,276,621,36,12,121,18,66,103,30,55,60,40,185,301,34,147,141,213,62,13,58,281,56,157,90,47,112,416,330,163,68,126,13,113,12,61,169,92,71,22,13,190,104,77,33,49,135,19,757,31,14,269,142,424,395,36,152,597,33,555,24,181,12,92,181,36,320,243,26,90,74,52,311,28,67,115,43,24,120,13,28,12,211,187,13,140,438,115,239,121,309,37,505,27,435,80,127,1185,93,118,13,149,66,79,354,19,104,15,298,230,59,63,355,61,34,252,63,138,121,199,149,91,51,27,36,93,211,81,26,41,17,188,721,44,103,29,93,358,100,32,35,68,254,270,140,72,354,185,50,171,189,83,134,13,206,652,54,19,485,17,121,192,34,138,19,160,23,42,44,95,300,64,170,457,282,601,207,27,768,33,246,183,208,522,125,214,57,175,43,166,240,18,24,108,121,45,113,163,63,282,20,92,43,19,88,37,188,274,423,38,123,110,544,146,74,38,19,39,64,230,12,177,513,20,72,40,264,29,266,275,405,78,269,12,39,99,226,107,83,99,24,99,606,167,191,130,105,142,34,455,108,106,34,426,62,64,20,261,72,105,548,201,153,72,103,218,103,277,148,114,224,89,377,734,37,33,290,132,758,157,48,20,41,13,139,128,51,38,134,59,191,849,90,136,59,12,250,268,187,610,82,83,101,61,28,35,88,29,77,25,90,139,99,88,115,72,245,156,74,653,52,43,82,434,68,261,57,66,23,57,55,295,1767,430,58,37,44,154,112,866,54,72,44,53,84,86,62,292,170,271,504,269,18,94,95,234,117,118,659,29,30,44,409,72,140,104,137,146,114,795,99,107,103,402,438,105,497,192,44,176,88,128,87,68,27,545,57,38,129,119,101,113,63,207,42,165,269,129,99,111,100,51,213,70,214,253,48,280,30,257,38,160,20,272,139,36,499,30,18,14,40,588,455,272,51,56,590,27,151,577,13,148,56,39,49,238,23,18,37,135,221,206,79,50,208,305,139,76,81,844,63,206,78,63,312,177,26,56,131,65,186,176,165,304,474,317,164,248,12,196,15,18,68,26,169,213,128,210,61,53,70,210,38,263,107,33,92,192,13,125,15,16,113,46,95,275,142,164,252,619,29,27,73,41,287,45,12,30,311,102,131,35,51,16,13,17,311,121,1376,75,80,263,35,24,277,43,21,157,97,308,110,224,76,159,177,53,19,90,104,92,56,107,100,38,713,12,103,76,142,20,53,42,30,93,160,147,19,236,450,115,241,57,16,47,37,226,25,327,52,285,249,12,78,105,51,21,13,148,559,16,85,176,273,218,266,264,190,20,23,32,36,64,24,193,166,165,40,448,244,17,55,72,16,86,330,107,498,306,35,27,43,498,355,320,111,262,47,976,157,481,83,379,49,31,184,21,109,43,1867,93,132,232,182,233,494,72,128,15,57,97,284,40,102,12,206,175,27,50,191,45,1519,203,14,125,73,87,37,17,271,236,161,53,111,21,14,174,70,259,251,168,182,36,175,127,337,185,203,897,386,160,202,44,194,213,530,94,19,111,65,187,90,38,14,13,30,195,106,39,9,256,109,28,168,169,216,207,356,180,115,39,296,16,129,55,24,170,37,17,123,234,36,87,304,31,115,697,34,36,260,50,72,100,12,271,40,35,31,12,555,105,126,139,168,578,48,168,80,57,302,218,58,383,53,27,32,606,757,181,31,34,399,55,82,22,1033,36,208,63,80,287,714,30,94,133,30,40,46,29,34,96,28,20,186,28,249,109,17,166,141,32,23,141,213,91,26,92,38,110,26,50,288,115,31,74,143,46,203,19,139,1119,50,178,108,124,724,286,38,97,54,44,12,121,138,142,156,122,66,57,94,75,75,91,84,26,229,140,14,487,26,52,26,54,239,127,176,22,80,73,94,51,74,94,33,27,61,160,144,190,367,567,64,94,68,69,121,240,91,56,250,288,26,204,400,22,48,27,128,111,167,85,352,21,47,57,52,25,357,19,29,151,742,26,47,250,185,118,353,17,15,128,128,46,50,65,57,26,28,33,63,319,42,45,306,313,33,72,143,36,41,240,353,100,73,351,13,149,331,56,53,46,44,32,81,1260,59,54,183,35,72,21,12,902,13,436,178,44,119,64,358,185,12,110,374,30,27,70,112,274,1227,83,129,92,58,114,21,108,19,32,79,252,99,31,333,312,46,236,88,264,102,34,110,23,52,481,12,17,429,50,409,38,57,13,14,26,132,179,35,44,1869,22,188,109,13,15,192,237,12,55,495,170,125,69,42,47,30,494,83,40,397,220,21,96,49,93,83,114,106,165,57,13,23,298,36,142,60,200,29,43,74,77,360,83,32,242,33,231,129,63,138,76,518,25,74,126,215,270,118,87,35,36,307,23,70,45,874,178,254,554,179,425,571,12,102,35,65,419,35,72,153,288,186,69,29,154,94,31,337,22,19,21,70,154,125,100,749,114,34,65,94,109,27,26,213,291,81,314,134,14,195,142,12,422,43,192,14,93,36,338,190,117,74,47,63,301,108,168,261,291,152,86,91,101,103,88,81,82,114,280,13,47,90,12,26,50,73,158,433,332,551,83,141,288,302,23,303,86,93,13,247,253,49,90,47,32,12,106,12,63,207,823,591,120,138,39,84,151,124,22,18,144,13,18,176,134,59,157,219,195,22,24,31,264,185,90,378,93,24,164,46,232,25,36,53,38,55,86,238,81,272,34,31,15,18,62,65,25,78,17,142,123,289,225,58,32,33,45,13,102,12,950,22,104,75,39,43,63,21,81,15,12,12,99,290,209,166,199,98,14,184,215,26,51,81,145,65,138,50,115,177,187,116,253,60,75,87,30,631,251,31,72,482,429,118,177,26,821,205,289,16,203,45,174,343,112,66,168,222,61,21,72,78,90,25,37,244,12,21,66,452,42,238,212,163,46,34,103,14,75,40,260,226,608,12,101,61,305,89,529,103,105,13,630,93,172,134,43,266,89,59,95,280,507,63,714,40,20,25,1019,49,63,84,37,18,367,74,87,14,15,368,36,91,95,423,76,177,184,569,176,31,287,857,62,103,68,312,236,139,368,195,79,73,15,309,73,53,141,28,42,199,27,40,118,791,218,34,203,60,511,25,20,48,17,69,190,157,220,89,157,192,17,533,98,30,268,59,101,123,38,71,157,290,180,269,45,27,125,16,54,229,107,136,173,321,126,163,77,70,234,27,64,13,144,420,37,492,62,20,54,167,36,83,21,32,11,54,22,139,167,221,16,23,347,376,31,39,26,100,244,154,24,233,31,82,90,536,13,152,254,19,261,87,34,82,10,26,70,310,20,437,262,62,41,400,132,294,95,25,62,1374,12,23,632,84,25,36,69,119,186,124,44,224,59,193,454,54,1111,1438,185,285,54,38,163,77,347,20,32,147,176,71,63,26,293,157,30,20,13,105,78,28,12,345,154,14,124,726,226,89,19,60,36,17,49,106,32,143,67,52,155,1377,49,51,888,367,257,54,265,20,295,73,106,69,28,178,59,182,64,67,116,227,85,59,158,174,20,43,166,61,128,291,22,17,36,34,37,65,265,457,13,119,118,52,309,110,369,294,124,52,148,13,57,21,139,264,27,22,74,362,108,153,80,42,202,323,571,12,42,334,112,51,68,53,51,55,201,44,24,29,45,79,1127,43,323,324,455,221,86,207,217,34,21,136,187,21,141,131,193,88,89,101,45,43,36,27,371,12,33,213,1902,682,69,32,321,59,99,108,13,237,318,302,35,29,227,206,60,58,33,208,594,304,65,28,96,111,203,117,34,17,96,230,52,26,31,61,161,20,28,58,51,51,88,407,365,56,23,36,181,105,80,38,63,94,35,125,77,171,185,446,28,24,200,121,14,136,28,33,40,106,132,102,148,51,62,92,44,75,89,35,12,183,63,182,642,58,261,37,337,74,52,90,236,18,66,62,19,182,19,61,19,25,646,26,135,91,47,145,46,49,177,51,125,22,103,12,512,30,201,47,27,109,173,69,146,46,107,30,252,36,28,101,39,47,118,63,50,78,508,52,92,167,13,79,294,138,444,20,15,209,80,664,141,52,50,164,48,126,51,24,30,121,16,121,56,37,695,22,72,44,41,44,37,128,1064,22,71,12,25,182,162,19,232,45,18,44,359,349,45,42,243,128,18,305,252,131,20,209,170,153,30,277,858,131,20,29,20,13,66,119,30,17,202,53,33,62,252,51,13,19,86,129,101,1034,54,31,233,87,49,20,37,208,14,161,65,78,37,124,16,36,168,435,192,31,33,12,92,41,13,170,358,12,926,304,125,58,198,59,1057,13,829,689,12,59,299,302,59,63,332,141,35,355,39,209,14,529,1089,166,36,54,55,40,453,197,74,214,100,330,19,214,55,36,80,32,28,299,107,32,354,317,113,103,20,30,242,84,12,17,95,176,85,77,50,42,251,71,63,53,37,24,57,163,26,257,671,151,29,584,35,15,65,78,233,115,314,216,90,118,79,17,38,546,64,180,23,676,51,24,13,84,75,9,626,142,36,51,75,22,37,144,40,22,157,111,52,66,95,41,883,236,118,26,105,44,50,263,55,814,386,70,102,628,112,40,462,453,71,41,193,115,152,83,76,364,42,55,31,114,24,118,314,38,293,58,847,269,59,545,369,66,282,389,30,123,218,120,619,46,38,27,13,61,156,160,43,178,181,27,473,271,142,161,177,13,18,17,47,547,61,265,31,154,114,80,312,120,131,123,74,51,77,568,122,68,1307,107,155,709,796,230,37,118,165,255,223,16,21,47,31,768,39,253,332,45,50,259,113,138,621,44,39,329,17,29,62,21,98,16,51,75,96,28,29,82,67,121,109,216,41,29,484,32,125,354,91,29,69,132,78,32,45,353,167,14,45,26,73,117,47,175,51,96,353,229,64,13,350,72,66,266,101,262,335,177,41,82,97,57,21,18,87,53,39,74,92,101,59,91,82,144,194,642,56,270,49,147,1064,199,435,38,529,35,14,384,118,23,45,106,78,81,103,32,74,67,509,1239,36,121,469,102,90,241,138,91,615,182,41,116,376,13,75,70,37,98,85,76,333,64,746,410,53,31,181,512,17,306,67,29,42,210,28,538,381,44,294,18,204,36,172,30,815,211,2159,29,59,197,157,16,59,38,269,355,59,75,22,60,210,227,99,39,54,65,765,79,81,20,233,154,116,191,60,189,23,64,84,105,28,20,53,301,86,316,12,220,307,98,142,33,137,114,105,130,92,44,809,152,43,15,67,181,43,130,25,120,374,55,63,34,418,17,72,902,393,497,44,115,20,60,97,45,292,69,13,28,76,96,51,470,12,114,17,85,61,45,220,30,1150,53,315,106,258,105,152,44,82,108,132,459,942,217,55,624,53,57,424,35,41,16,24,56,485,167,33,42,216,577,43,41,615,41,49,43,24,33,121,42,19,33,31,95,30,114,52,352,66,122,134,30,79,89,394,39,32,343,21,27,40,20,189,141,152,358,43,117,206,81,145,80,361,85,15,97,12,39,35,190,660,45,99,28,106,35,70,17,164,69,33,31,29,381,110,392,361,984,89,214,632,24,49,121,170,412,92,2457,44,80,63,378,42,25,380,50,154,406,874,65,43,13,93,115,220,249,211,114,297,211,562,110,282,54,72,73,104,605,25,53,188,87,314,1090,102,13,454,38,120,188,148,232,170,205,108,170,128,162,28,22,44,271,77,77,28,113,19,107,22,229,199,108,41,232,420,31,24,459,406,395,328,203,383,80,12,196,97,17,470,29,179,14,55,106,29,680,48,56,44,382,284,53,69,173,13,78,49,310,586,117,89,37,220,370,153,314,344,152,12,296,83,51,198,111,118,59,1202,18,40,438,135,216,737,96,18,40,140,69,361,13,56,68,158,145,130,30,981,582,154,66,166,574,35,39,47,96,37,176,50,107,335,18,59,141,59,15,16,123,388,275,23,26,74,30,34,116,12,251,51,36,51,382,179,40,29,76,616,361,63,219,34,34,84,340,44,252,76,496,69,69,29,30,81,1347,739,1061,103,117,134,773,839,1077,687,270,104,32,116,41,38,15,12,248,149,68,92,22,68,20,302,78,61,69,516,149,26,20,108,161,57,23,31,125,495,267,241,104,463,87,106,901,193,92,31,582,25,31,161,281,48,75,361,166,18,55,34,151,1119,75,12,61,60,216,125,468,58,164,26,14,106,68,68,78,26,39,90,26,328,165,12,44,23,28,41,15,395,60,43,41,85,326,39,21,383,238,51,28,993,454,63,26,27,378,114,65,93,29,104,121,331,280,85,12,34,115,89,86,308,1235,84,96,100,51,78,71,414,18,198,201,237,38,66,78,344,182,64,135,62,107,287,23,45,292,29,35,78,484,60,196,236,248,53,21,52,52,30,310,75,169,53,22,293,55,234,200,107,93,342,32,128,159,35,111,12,42,72,30,19,41,134,98,254,450,25,186,120,43,24,180,42,382,137,30,30,753,131,225,268,202,96,81,116,40,27,236,16,25,66,49,24,109,55,52,68,121,89,560,61,58,21,22,188,29,70,62,1021,39,119,451,191,157,234,106,12,138,45,83,216,22,131,65,93,928,244,157,65,114,97,27,279,35,14,30,101,756,44,60,15,29,16,578,74,179,192,85,55,28,107,116,282,101,13,53,103,119,551,32,466,82,16,330,365,24,181,98,348,22,171,99,26,29,56,74,26,188,464,212,46,584,75,48,436,24,111,27,182,39,58,654,67,221,21,251,63,74,111,13,208,45,99,80,224,62,376,20,55,39,102,38,136,52,388,26,114,18,600,22,432,27,58,103,248,144,74,81,12,137,434,100,463,170,41,13,25,120,173,22,296,101,356,13,84,37,103,131,197,132,17,59,522,41,567,21,136,112,56,434,95,93,228,159,165,124,212,149,113,18,57,778,134,116,206,28,83,26,103,29,163,63,165,65,389,342,31,78,240,82,37,197,385,34,86,45,31,129,97,69,124,89,26,97,1143,294,147,260,210,158,79,89,100,285,88,97,499,31,290,83,173,150,85,223,59,61,288,428,17,438,245,103,94,222,217,159,233,163,35,53,150,18,14,88,94,80,206,258,64,147,64,223,531,332,226,12,111,359,72,239,68,40,12,18,96,53,856,33,991,29,86,847,177,138,41,379,372,176,18,54,18,324,27,200,155,18,17,83,44,89,125,17,100,166,82,49,21,39,146,139,646,215,831,9,99,30,190,546,78,478,88,55,87,76,215,320,61,68,44,147,21,107,95,101,12,39,905,18,20,65,30,93,47,38,55,22,88,231,19,300,100,36,115,168,31,169,140,96,132,133,12,47,42,35,83,175,197,52,133,102,106,921,155,203,300,154,38,12,184,160,280,51,202,111,34,155,91,119,102,54,70,20,130,79,13,80,207,104,142,106,73,158,153,35,12,700,71,31,126,77,632,494,37,60,129,205,45,16,27,16,56,51,35,88,54,23,47,47,40,79,142,13,25,39,3416,108,24,167,26,49,401,33,89,57,250,115,429,23,223,41,453,110,21,16,20,159,26,53,83,56,150,16,182,107,123,164,27,67,24,28,26,298,22,230,31,14,181,59,94,254,72,158,84,267,51,483,32,39,39,18,178,153,77,184,111,17,1448,289,110,169,104,50,312,118,60,18,26,34,172,148,116,19,37,57,34,21,139,57,153,63,13,27,792,221,148,548,13,300,141,137,60,68,420,21,32,63,78,63,156,48,12,1901,22,63,132,35,112,25,13,13,33,104,287,26,12,406,212,41,87,183,43,13,827,18,1046,65,98,439,237,66,215,47,12,43,107,16,47,69,56,71,29,46,101,71,36,211,86,23,18,20,141,111,56,585,103,222,50,210,200,51,89,37,41,62,77,131,82,127,736,97,71,36,139,27,193,195,91,110,390,551,86,57,203,157,129,648,312,215,42,49,27,285,41,365,135,205,53,90,166,22,105,16,407,31,247,804,49,174,70,154,104,20,73,896,176,69,41,189,22,94,185,42,37};
int answer[20000];
double Htoi[300][300];
void build_similar(int n)
{
	const char *chrlist="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
 	for(int i=0;i<62;i++)
		for(int j=0;j<62;j++)
            Htoi[chrlist[i]][chrlist[j]]=62*chrtoi(chrlist[i])+chrtoi(chrlist[j]);
 	char *pos=sim_s;
 	double AND=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			AND=Htoi[*pos][*(pos+1)];
			similar[j][i]=similar[i][j]=AND/(token_set_size[i]+token_set_size[j]-AND);
			pos+=2;
		}
	}
}
int main()
{
	api_init(&n_mails, &n_queries, &mails, &queries);
	build_similar(10000);
 	for(int qid=0;qid<n_queries;qid++)
	{
		if( queries[qid].reward>57 && queries[qid].type==find_similar)
		{
			int ans_len = 0, mid = queries[qid].data.find_similar_data.mid;
			double threshold = queries[qid].data.find_similar_data.threshold;
			for(int i=0;i<n_mails;i++)
			{
				if(i!=mid&&similar[mid][i]>threshold)
					answer[ans_len++]=i;
			}
			api.answer(qid,answer,ans_len);
		}
	}
	return 0;
}

