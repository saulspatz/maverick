SOURCES=$(wildcard src/dist*.c)
OBJECTS=$(patsubst src/%.c, build/%.o, $(SOURCES))

CFLAGS := -O3 -Wall -g 

$(OBJECTS): build/%.o : src/%.c
	gcc $(CFLAGS) -Iinclude  $< -o $@

build/dist1312.o: include/spades13.h include/hearts12.h card.h
build/dist13111.o: include/spades13.h include/hearts11.h include/diamonds1.h card.h
build/dist13102.o: include/spades13.h include/hearts10.h include/diamonds2.h card.h
build/dist131011.o: include/spades13.h include/hearts10.h include/diamonds1.h include/clubs1.h card.h
build/dist1393.o: include/spades13.h include/hearts9.h include/diamonds3.h card.h
build/dist13921.o: include/spades13.h include/hearts9.h include/diamonds2.h include/clubs1.h card.h
build/dist1384.o: include/spades13.h include/hearts8.h include/diamonds4.h card.h
build/dist13831.o: include/spades13.h include/hearts8.h include/diamonds3.h include/clubs1.h card.h
build/dist13822.o: include/spades13.h include/hearts8.h include/diamonds2.h include/clubs2.h card.h
build/dist1375.o: include/spades13.h include/hearts7.h include/diamonds5.h card.h
build/dist13741.o: include/spades13.h include/hearts7.h include/diamonds4.h include/clubs1.h card.h
build/dist13732.o: include/spades13.h include/hearts7.h include/diamonds3.h include/clubs2.h card.h
build/dist1366.o: include/spades13.h include/hearts6.h include/diamonds6.h card.h
build/dist13651.o: include/spades13.h include/hearts6.h include/diamonds5.h include/clubs1.h card.h
build/dist13642.o: include/spades13.h include/hearts6.h include/diamonds4.h include/clubs2.h card.h
build/dist13633.o: include/spades13.h include/hearts6.h include/diamonds3.h include/clubs3.h card.h
build/dist13552.o: include/spades13.h include/hearts5.h include/diamonds5.h include/clubs2.h card.h
build/dist13543.o: include/spades13.h include/hearts5.h include/diamonds4.h include/clubs3.h card.h
build/dist13444.o: include/spades13.h include/hearts4.h include/diamonds4.h include/clubs4.h card.h
build/dist12121.o: include/spades12.h include/hearts12.h include/diamonds1.h card.h
build/dist12112.o: include/spades12.h include/hearts11.h include/diamonds2.h card.h
build/dist121111.o: include/spades12.h include/hearts11.h include/diamonds1.h include/clubs1.h card.h
build/dist12103.o: include/spades12.h include/hearts10.h include/diamonds3.h card.h
build/dist121021.o: include/spades12.h include/hearts10.h include/diamonds2.h include/clubs1.h card.h
build/dist1294.o: include/spades12.h include/hearts9.h include/diamonds4.h card.h
build/dist12931.o: include/spades12.h include/hearts9.h include/diamonds3.h include/clubs1.h card.h
build/dist12922.o: include/spades12.h include/hearts9.h include/diamonds2.h include/clubs2.h card.h
build/dist1285.o: include/spades12.h include/hearts8.h include/diamonds5.h card.h
build/dist12841.o: include/spades12.h include/hearts8.h include/diamonds4.h include/clubs1.h card.h
build/dist12832.o: include/spades12.h include/hearts8.h include/diamonds3.h include/clubs2.h card.h
build/dist1276.o: include/spades12.h include/hearts7.h include/diamonds6.h card.h
build/dist12751.o: include/spades12.h include/hearts7.h include/diamonds5.h include/clubs1.h card.h
build/dist12742.o: include/spades12.h include/hearts7.h include/diamonds4.h include/clubs2.h card.h
build/dist12733.o: include/spades12.h include/hearts7.h include/diamonds3.h include/clubs3.h card.h
build/dist12661.o: include/spades12.h include/hearts6.h include/diamonds6.h include/clubs1.h card.h
build/dist12652.o: include/spades12.h include/hearts6.h include/diamonds5.h include/clubs2.h card.h
build/dist12643.o: include/spades12.h include/hearts6.h include/diamonds4.h include/clubs3.h card.h
build/dist12553.o: include/spades12.h include/hearts5.h include/diamonds5.h include/clubs3.h card.h
build/dist12544.o: include/spades12.h include/hearts5.h include/diamonds4.h include/clubs4.h card.h
build/dist11113.o: include/spades11.h include/hearts11.h include/diamonds3.h card.h
build/dist111121.o: include/spades11.h include/hearts11.h include/diamonds2.h include/clubs1.h card.h
build/dist11104.o: include/spades11.h include/hearts10.h include/diamonds4.h card.h
build/dist111031.o: include/spades11.h include/hearts10.h include/diamonds3.h include/clubs1.h card.h
build/dist111022.o: include/spades11.h include/hearts10.h include/diamonds2.h include/clubs2.h card.h
build/dist1195.o: include/spades11.h include/hearts9.h include/diamonds5.h card.h
build/dist11941.o: include/spades11.h include/hearts9.h include/diamonds4.h include/clubs1.h card.h
build/dist11932.o: include/spades11.h include/hearts9.h include/diamonds3.h include/clubs2.h card.h
build/dist1186.o: include/spades11.h include/hearts8.h include/diamonds6.h card.h
build/dist11851.o: include/spades11.h include/hearts8.h include/diamonds5.h include/clubs1.h card.h
build/dist11842.o: include/spades11.h include/hearts8.h include/diamonds4.h include/clubs2.h card.h
build/dist11833.o: include/spades11.h include/hearts8.h include/diamonds3.h include/clubs3.h card.h
build/dist1177.o: include/spades11.h include/hearts7.h include/diamonds7.h card.h
build/dist11761.o: include/spades11.h include/hearts7.h include/diamonds6.h include/clubs1.h card.h
build/dist11752.o: include/spades11.h include/hearts7.h include/diamonds5.h include/clubs2.h card.h
build/dist11743.o: include/spades11.h include/hearts7.h include/diamonds4.h include/clubs3.h card.h
build/dist11662.o: include/spades11.h include/hearts6.h include/diamonds6.h include/clubs2.h card.h
build/dist11653.o: include/spades11.h include/hearts6.h include/diamonds5.h include/clubs3.h card.h
build/dist11644.o: include/spades11.h include/hearts6.h include/diamonds4.h include/clubs4.h card.h
build/dist11554.o: include/spades11.h include/hearts5.h include/diamonds5.h include/clubs4.h card.h
build/dist10105.o: include/spades10.h include/hearts10.h include/diamonds5.h card.h
build/dist101041.o: include/spades10.h include/hearts10.h include/diamonds4.h include/clubs1.h card.h
build/dist101032.o: include/spades10.h include/hearts10.h include/diamonds3.h include/clubs2.h card.h
build/dist1096.o: include/spades10.h include/hearts9.h include/diamonds6.h card.h
build/dist10951.o: include/spades10.h include/hearts9.h include/diamonds5.h include/clubs1.h card.h
build/dist10942.o: include/spades10.h include/hearts9.h include/diamonds4.h include/clubs2.h card.h
build/dist10933.o: include/spades10.h include/hearts9.h include/diamonds3.h include/clubs3.h card.h
build/dist1087.o: include/spades10.h include/hearts8.h include/diamonds7.h card.h
build/dist10861.o: include/spades10.h include/hearts8.h include/diamonds6.h include/clubs1.h card.h
build/dist10852.o: include/spades10.h include/hearts8.h include/diamonds5.h include/clubs2.h card.h
build/dist10843.o: include/spades10.h include/hearts8.h include/diamonds4.h include/clubs3.h card.h
build/dist10771.o: include/spades10.h include/hearts7.h include/diamonds7.h include/clubs1.h card.h
build/dist10762.o: include/spades10.h include/hearts7.h include/diamonds6.h include/clubs2.h card.h
build/dist10753.o: include/spades10.h include/hearts7.h include/diamonds5.h include/clubs3.h card.h
build/dist10744.o: include/spades10.h include/hearts7.h include/diamonds4.h include/clubs4.h card.h
build/dist10663.o: include/spades10.h include/hearts6.h include/diamonds6.h include/clubs3.h card.h
build/dist10654.o: include/spades10.h include/hearts6.h include/diamonds5.h include/clubs4.h card.h
build/dist10555.o: include/spades10.h include/hearts5.h include/diamonds5.h include/clubs5.h card.h
build/dist997.o: include/spades9.h include/hearts9.h include/diamonds7.h card.h
build/dist9961.o: include/spades9.h include/hearts9.h include/diamonds6.h include/clubs1.h card.h
build/dist9952.o: include/spades9.h include/hearts9.h include/diamonds5.h include/clubs2.h card.h
build/dist9943.o: include/spades9.h include/hearts9.h include/diamonds4.h include/clubs3.h card.h
build/dist988.o: include/spades9.h include/hearts8.h include/diamonds8.h card.h
build/dist9871.o: include/spades9.h include/hearts8.h include/diamonds7.h include/clubs1.h card.h
build/dist9862.o: include/spades9.h include/hearts8.h include/diamonds6.h include/clubs2.h card.h
build/dist9853.o: include/spades9.h include/hearts8.h include/diamonds5.h include/clubs3.h card.h
build/dist9844.o: include/spades9.h include/hearts8.h include/diamonds4.h include/clubs4.h card.h
build/dist9772.o: include/spades9.h include/hearts7.h include/diamonds7.h include/clubs2.h card.h
build/dist9763.o: include/spades9.h include/hearts7.h include/diamonds6.h include/clubs3.h card.h
build/dist9754.o: include/spades9.h include/hearts7.h include/diamonds5.h include/clubs4.h card.h
build/dist9664.o: include/spades9.h include/hearts6.h include/diamonds6.h include/clubs4.h card.h
build/dist9655.o: include/spades9.h include/hearts6.h include/diamonds5.h include/clubs5.h card.h
build/dist8881.o: include/spades8.h include/hearts8.h include/diamonds8.h include/clubs1.h card.h
build/dist8872.o: include/spades8.h include/hearts8.h include/diamonds7.h include/clubs2.h card.h
build/dist8863.o: include/spades8.h include/hearts8.h include/diamonds6.h include/clubs3.h card.h
build/dist8854.o: include/spades8.h include/hearts8.h include/diamonds5.h include/clubs4.h card.h
build/dist8773.o: include/spades8.h include/hearts7.h include/diamonds7.h include/clubs3.h card.h
build/dist8764.o: include/spades8.h include/hearts7.h include/diamonds6.h include/clubs4.h card.h
build/dist8755.o: include/spades8.h include/hearts7.h include/diamonds5.h include/clubs5.h card.h
build/dist8665.o: include/spades8.h include/hearts6.h include/diamonds6.h include/clubs5.h card.h
build/dist7774.o: include/spades7.h include/hearts7.h include/diamonds7.h include/clubs4.h card.h
build/dist7765.o: include/spades7.h include/hearts7.h include/diamonds6.h include/clubs5.h card.h
build/dist7666.o: include/spades7.h include/hearts6.h include/diamonds6.h include/clubs6.h card.h
