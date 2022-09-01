SOURCES=$(wildcard ../src/dist*.c)
OBJECTS=$(patsubst ../src/%.c, %.o, $(SOURCES))
SUITS = $(wildcard dist*.h)
VPATH = ../include
vpath %.c ../src

INCLUDE = ../include
CFLAGS := -O3 -Wall -g -std=c11 -I$(INCLUDE)
CC := gcc


maverick: maverick.o $(OBJECTS)
	$(CC) $(CFLAGS) maverick.o $(OBJECTS) -o $@

$(OBJECTS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

maverick.c: suits.h externs.h tasks.h

maverick.o: maverick.c suits.h tasks.h types.h externs.h
suits.h: $(SUITS)

dist1312.o: spades13.h hearts12.h types.h
dist13111.o: spades13.h hearts11.h diamonds1.h types.h
dist13102.o: spades13.h hearts10.h diamonds2.h types.h
dist131011.o:spades13.h hearts10.h diamonds1.h clubs1.h types.h
dist1393.o: spades13.h hearts9.h diamonds3.h types.h
dist13921.o:spades13.h hearts9.h diamonds2.h clubs1.h types.h
dist1384.o: spades13.h hearts8.h diamonds4.h types.h
dist13831.o:spades13.h hearts8.h diamonds3.h clubs1.h types.h
dist13822.o:spades13.h hearts8.h diamonds2.h clubs2.h types.h
dist1375.o: spades13.h hearts7.h diamonds5.h types.h
dist13741.o:spades13.h hearts7.h diamonds4.h clubs1.h types.h
dist13732.o:spades13.h hearts7.h diamonds3.h clubs2.h types.h
dist1366.o: spades13.h hearts6.h diamonds6.h types.h
dist13651.o:spades13.h hearts6.h diamonds5.h clubs1.h types.h
dist13642.o:spades13.h hearts6.h diamonds4.h clubs2.h types.h
dist13633.o:spades13.h hearts6.h diamonds3.h clubs3.h types.h
dist13552.o:spades13.h hearts5.h diamonds5.h clubs2.h types.h
dist13543.o:spades13.h hearts5.h diamonds4.h clubs3.h types.h
dist13444.o:spades13.h hearts4.h diamonds4.h clubs4.h types.h
dist12121.o: spades12.h hearts12.h diamonds1.h types.h
dist12112.o: spades12.h hearts11.h diamonds2.h types.h
dist121111.o:spades12.h hearts11.h diamonds1.h clubs1.h types.h
dist12103.o: spades12.h hearts10.h diamonds3.h types.h
dist121021.o:spades12.h hearts10.h diamonds2.h clubs1.h types.h
dist1294.o: spades12.h hearts9.h diamonds4.h types.h
dist12931.o:spades12.h hearts9.h diamonds3.h clubs1.h types.h
dist12922.o:spades12.h hearts9.h diamonds2.h clubs2.h types.h
dist1285.o: spades12.h hearts8.h diamonds5.h types.h
dist12841.o:spades12.h hearts8.h diamonds4.h clubs1.h types.h
dist12832.o:spades12.h hearts8.h diamonds3.h clubs2.h types.h
dist1276.o: spades12.h hearts7.h diamonds6.h types.h
dist12751.o:spades12.h hearts7.h diamonds5.h clubs1.h types.h
dist12742.o:spades12.h hearts7.h diamonds4.h clubs2.h types.h
dist12733.o:spades12.h hearts7.h diamonds3.h clubs3.h types.h
dist12661.o:spades12.h hearts6.h diamonds6.h clubs1.h types.h
dist12652.o:spades12.h hearts6.h diamonds5.h clubs2.h types.h
dist12643.o:spades12.h hearts6.h diamonds4.h clubs3.h types.h
dist12553.o:spades12.h hearts5.h diamonds5.h clubs3.h types.h
dist12544.o:spades12.h hearts5.h diamonds4.h clubs4.h types.h
dist11113.o: spades11.h hearts11.h diamonds3.h types.h
dist111121.o:spades11.h hearts11.h diamonds2.h clubs1.h types.h
dist11104.o: spades11.h hearts10.h diamonds4.h types.h
dist111031.o:spades11.h hearts10.h diamonds3.h clubs1.h types.h
dist111022.o:spades11.h hearts10.h diamonds2.h clubs2.h types.h
dist1195.o: spades11.h hearts9.h diamonds5.h types.h
dist11941.o:spades11.h hearts9.h diamonds4.h clubs1.h types.h
dist11932.o:spades11.h hearts9.h diamonds3.h clubs2.h types.h
dist1186.o: spades11.h hearts8.h diamonds6.h types.h
dist11851.o:spades11.h hearts8.h diamonds5.h clubs1.h types.h
dist11842.o:spades11.h hearts8.h diamonds4.h clubs2.h types.h
dist11833.o:spades11.h hearts8.h diamonds3.h clubs3.h types.h
dist1177.o: spades11.h hearts7.h diamonds7.h types.h
dist11761.o:spades11.h hearts7.h diamonds6.h clubs1.h types.h
dist11752.o:spades11.h hearts7.h diamonds5.h clubs2.h types.h
dist11743.o:spades11.h hearts7.h diamonds4.h clubs3.h types.h
dist11662.o:spades11.h hearts6.h diamonds6.h clubs2.h types.h
dist11653.o:spades11.h hearts6.h diamonds5.h clubs3.h types.h
dist11644.o:spades11.h hearts6.h diamonds4.h clubs4.h types.h
dist11554.o:spades11.h hearts5.h diamonds5.h clubs4.h types.h
dist10105.o: spades10.h hearts10.h diamonds5.h types.h
dist101041.o:spades10.h hearts10.h diamonds4.h clubs1.h types.h
dist101032.o:spades10.h hearts10.h diamonds3.h clubs2.h types.h
dist1096.o: spades10.h hearts9.h diamonds6.h types.h
dist10951.o:spades10.h hearts9.h diamonds5.h clubs1.h types.h
dist10942.o:spades10.h hearts9.h diamonds4.h clubs2.h types.h
dist10933.o:spades10.h hearts9.h diamonds3.h clubs3.h types.h
dist1087.o: spades10.h hearts8.h diamonds7.h types.h
dist10861.o:spades10.h hearts8.h diamonds6.h clubs1.h types.h
dist10852.o:spades10.h hearts8.h diamonds5.h clubs2.h types.h
dist10843.o:spades10.h hearts8.h diamonds4.h clubs3.h types.h
dist10771.o:spades10.h hearts7.h diamonds7.h clubs1.h types.h
dist10762.o:spades10.h hearts7.h diamonds6.h clubs2.h types.h
dist10753.o:spades10.h hearts7.h diamonds5.h clubs3.h types.h
dist10744.o:spades10.h hearts7.h diamonds4.h clubs4.h types.h
dist10663.o:spades10.h hearts6.h diamonds6.h clubs3.h types.h
dist10654.o:spades10.h hearts6.h diamonds5.h clubs4.h types.h
dist10555.o:spades10.h hearts5.h diamonds5.h clubs5.h types.h
dist997.o: spades9.h hearts9.h diamonds7.h types.h
dist9961.o:spades9.h hearts9.h diamonds6.h clubs1.h types.h
dist9952.o:spades9.h hearts9.h diamonds5.h clubs2.h types.h
dist9943.o:spades9.h hearts9.h diamonds4.h clubs3.h types.h
dist988.o: spades9.h hearts8.h diamonds8.h types.h
dist9871.o:spades9.h hearts8.h diamonds7.h clubs1.h types.h
dist9862.o:spades9.h hearts8.h diamonds6.h clubs2.h types.h
dist9853.o:spades9.h hearts8.h diamonds5.h clubs3.h types.h
dist9844.o:spades9.h hearts8.h diamonds4.h clubs4.h types.h
dist9772.o:spades9.h hearts7.h diamonds7.h clubs2.h types.h
dist9763.o:spades9.h hearts7.h diamonds6.h clubs3.h types.h
dist9754.o:spades9.h hearts7.h diamonds5.h clubs4.h types.h
dist9664.o:spades9.h hearts6.h diamonds6.h clubs4.h types.h
dist9655.o:spades9.h hearts6.h diamonds5.h clubs5.h types.h
dist8881.o:spades8.h hearts8.h diamonds8.h clubs1.h types.h
dist8872.o:spades8.h hearts8.h diamonds7.h clubs2.h types.h
dist8863.o:spades8.h hearts8.h diamonds6.h clubs3.h types.h
dist8854.o:spades8.h hearts8.h diamonds5.h clubs4.h types.h
dist8773.o:spades8.h hearts7.h diamonds7.h clubs3.h types.h
dist8764.o:spades8.h hearts7.h diamonds6.h clubs4.h types.h
dist8755.o:spades8.h hearts7.h diamonds5.h clubs5.h types.h
dist8665.o:spades8.h hearts6.h diamonds6.h clubs5.h types.h
dist7774.o:spades7.h hearts7.h diamonds7.h clubs4.h types.h
dist7765.o:spades7.h hearts7.h diamonds6.h clubs5.h types.h
dist7666.o:spades7.h hearts6.h diamonds6.h clubs6.h types.h
