SOURCES=$(wildcard ../src/dist*.c)
OBJECTS=$(patsubst ../src/%.c, %.o, $(SOURCES))
SUITS = $(wildcard dist*.h)
VPATH = ../include
vpath %.c ../src

INCLUDE = ../include
CFLAGS := -O3 -Wall -g -std=c11 -I$(INCLUDE)
CC := gcc


maverick: maverick.o $(OBJECTS)
	python ../scripts/tasks.py
	$(CC) $(CFLAGS) maverick.o $(OBJECTS) -o $@

$(OBJECTS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

maverick.c: suits.h externs.h tasks.h

maverick.o: maverick.c suits.h tasks.h types.h externs.h
suits.h: $(SUITS)

dist11_6_5_3.o: ../include/types.h ../include/suit11.h ../include/ranks6.h ../include/suit5.h ../include/suit3.h 
dist9_8_5_3.o: ../include/types.h ../include/suit9.h ../include/ranks8.h ../include/suit5.h ../include/suit3.h 
dist13_10_2_0.o: ../include/types.h ../include/suit13.h ../include/ranks10.h ../include/suit2.h 
dist8_8_7_2.o: ../include/types.h ../include/suit8.h ../include/suit8.h ../include/ranks7.h ../include/suit2.h 
dist10_8_5_2.o: ../include/types.h ../include/suit10.h ../include/ranks8.h ../include/suit5.h ../include/suit2.h 
dist11_7_7_0.o: ../include/types.h ../include/ranks11.h ../include/suit7.h ../include/suit7.h 
dist12_11_2_0.o: ../include/types.h ../include/suit12.h ../include/ranks11.h ../include/suit2.h 
dist8_8_5_4.o: ../include/types.h ../include/suit8.h ../include/suit8.h ../include/ranks5.h ../include/suit4.h 
dist12_10_3_0.o: ../include/types.h ../include/suit12.h ../include/ranks10.h ../include/suit3.h 
dist13_7_3_2.o: ../include/types.h ../include/suit13.h ../include/ranks7.h ../include/suit3.h ../include/suit2.h 
dist11_11_3_0.o: ../include/types.h ../include/suit11.h ../include/suit11.h ../include/ranks3.h 
dist10_7_7_1.o: ../include/types.h ../include/suit7.h ../include/suit7.h ../include/ranks10.h ../include/suit1.h 
dist7_6_6_6.o: ../include/types.h ../include/ranks7.h ../include/suit6.h ../include/suit6.h ../include/suit6.h 
dist9_8_6_2.o: ../include/types.h ../include/suit9.h ../include/suit8.h ../include/ranks6.h ../include/suit2.h 
dist12_9_4_0.o: ../include/types.h ../include/suit12.h ../include/ranks9.h ../include/suit4.h 
dist9_7_7_2.o: ../include/types.h ../include/suit7.h ../include/suit7.h ../include/ranks9.h ../include/suit2.h 
dist10_9_5_1.o: ../include/types.h ../include/suit10.h ../include/suit9.h ../include/ranks5.h ../include/suit1.h 
dist11_5_5_4.o: ../include/types.h ../include/suit5.h ../include/suit5.h ../include/suit11.h ../include/ranks4.h 
dist13_8_4_0.o: ../include/types.h ../include/suit13.h ../include/ranks8.h ../include/suit4.h 
dist12_6_6_1.o: ../include/types.h ../include/suit6.h ../include/suit6.h ../include/ranks12.h ../include/suit1.h 
dist13_6_3_3.o: ../include/types.h ../include/suit3.h ../include/suit3.h ../include/suit13.h ../include/ranks6.h 
dist9_8_7_1.o: ../include/types.h ../include/suit9.h ../include/suit8.h ../include/ranks7.h ../include/suit1.h 
dist12_7_4_2.o: ../include/types.h ../include/suit12.h ../include/ranks7.h ../include/suit4.h ../include/suit2.h 
dist13_4_4_4.o: ../include/types.h ../include/ranks13.h ../include/suit4.h ../include/suit4.h ../include/suit4.h 
dist10_8_7_0.o: ../include/types.h ../include/suit10.h ../include/suit8.h ../include/ranks7.h 
dist11_7_5_2.o: ../include/types.h ../include/suit11.h ../include/ranks7.h ../include/suit5.h ../include/suit2.h 
dist7_7_6_5.o: ../include/types.h ../include/suit7.h ../include/suit7.h ../include/ranks6.h ../include/suit5.h 
dist11_6_6_2.o: ../include/types.h ../include/suit6.h ../include/suit6.h ../include/ranks11.h ../include/suit2.h 
dist12_5_5_3.o: ../include/types.h ../include/suit5.h ../include/suit5.h ../include/suit12.h ../include/ranks3.h 
dist10_10_4_1.o: ../include/types.h ../include/suit10.h ../include/suit10.h ../include/ranks4.h ../include/suit1.h 
dist9_9_7_0.o: ../include/types.h ../include/suit9.h ../include/suit9.h ../include/ranks7.h 
dist11_8_6_0.o: ../include/types.h ../include/suit11.h ../include/suit8.h ../include/ranks6.h 
dist12_6_5_2.o: ../include/types.h ../include/suit12.h ../include/ranks6.h ../include/suit5.h ../include/suit2.h 
dist10_6_5_4.o: ../include/types.h ../include/suit10.h ../include/ranks6.h ../include/suit5.h ../include/suit4.h 
dist13_7_4_1.o: ../include/types.h ../include/suit13.h ../include/ranks7.h ../include/suit4.h ../include/suit1.h 
dist12_9_3_1.o: ../include/types.h ../include/suit12.h ../include/ranks9.h ../include/suit3.h ../include/suit1.h 
dist8_8_8_1.o: ../include/types.h ../include/suit8.h ../include/suit8.h ../include/suit8.h ../include/ranks1.h 
dist11_6_4_4.o: ../include/types.h ../include/suit4.h ../include/suit4.h ../include/suit11.h ../include/ranks6.h 
dist13_10_1_1.o: ../include/types.h ../include/suit1.h ../include/suit1.h ../include/suit13.h ../include/ranks10.h 
dist11_11_2_1.o: ../include/types.h ../include/suit11.h ../include/suit11.h ../include/ranks2.h ../include/suit1.h 
dist11_7_6_1.o: ../include/types.h ../include/suit11.h ../include/ranks7.h ../include/suit6.h ../include/suit1.h 
dist12_7_5_1.o: ../include/types.h ../include/suit12.h ../include/ranks7.h ../include/suit5.h ../include/suit1.h 
dist13_7_5_0.o: ../include/types.h ../include/suit13.h ../include/ranks7.h ../include/suit5.h 
dist11_8_4_2.o: ../include/types.h ../include/suit11.h ../include/ranks8.h ../include/suit4.h ../include/suit2.h 
dist13_8_2_2.o: ../include/types.h ../include/suit2.h ../include/suit2.h ../include/suit13.h ../include/ranks8.h 
dist13_6_5_1.o: ../include/types.h ../include/suit13.h ../include/ranks6.h ../include/suit5.h ../include/suit1.h 
dist8_7_6_4.o: ../include/types.h ../include/suit8.h ../include/ranks7.h ../include/suit6.h ../include/suit4.h 
dist10_7_4_4.o: ../include/types.h ../include/suit4.h ../include/suit4.h ../include/suit10.h ../include/ranks7.h 
dist9_6_6_4.o: ../include/types.h ../include/suit6.h ../include/suit6.h ../include/ranks9.h ../include/suit4.h 
dist12_8_4_1.o: ../include/types.h ../include/suit12.h ../include/ranks8.h ../include/suit4.h ../include/suit1.h 
dist11_8_5_1.o: ../include/types.h ../include/suit11.h ../include/ranks8.h ../include/suit5.h ../include/suit1.h 
dist10_8_6_1.o: ../include/types.h ../include/suit10.h ../include/suit8.h ../include/ranks6.h ../include/suit1.h 
dist10_9_4_2.o: ../include/types.h ../include/suit10.h ../include/ranks9.h ../include/suit4.h ../include/suit2.h 
dist12_8_5_0.o: ../include/types.h ../include/suit12.h ../include/ranks8.h ../include/suit5.h 
dist9_9_4_3.o: ../include/types.h ../include/suit9.h ../include/suit9.h ../include/ranks4.h ../include/suit3.h 
dist12_6_4_3.o: ../include/types.h ../include/suit12.h ../include/ranks6.h ../include/suit4.h ../include/suit3.h 
dist7_7_7_4.o: ../include/types.h ../include/suit7.h ../include/suit7.h ../include/suit7.h ../include/ranks4.h 
dist12_10_2_1.o: ../include/types.h ../include/suit12.h ../include/ranks10.h ../include/suit2.h ../include/suit1.h 
dist9_6_5_5.o: ../include/types.h ../include/suit5.h ../include/suit5.h ../include/suit9.h ../include/ranks6.h 
dist9_7_6_3.o: ../include/types.h ../include/suit9.h ../include/ranks7.h ../include/suit6.h ../include/suit3.h 
dist13_9_3_0.o: ../include/types.h ../include/suit13.h ../include/ranks9.h ../include/suit3.h 
dist9_7_5_4.o: ../include/types.h ../include/suit9.h ../include/ranks7.h ../include/suit5.h ../include/suit4.h 
dist11_8_3_3.o: ../include/types.h ../include/suit3.h ../include/suit3.h ../include/suit11.h ../include/ranks8.h 
dist12_7_6_0.o: ../include/types.h ../include/suit12.h ../include/ranks7.h ../include/suit6.h 
dist11_10_3_1.o: ../include/types.h ../include/suit11.h ../include/ranks10.h ../include/suit3.h ../include/suit1.h 
dist9_8_4_4.o: ../include/types.h ../include/suit4.h ../include/suit4.h ../include/suit9.h ../include/ranks8.h 
dist12_11_1_1.o: ../include/types.h ../include/suit1.h ../include/suit1.h ../include/suit12.h ../include/ranks11.h 
dist11_9_3_2.o: ../include/types.h ../include/suit11.h ../include/ranks9.h ../include/suit3.h ../include/suit2.h 
dist8_6_6_5.o: ../include/types.h ../include/suit6.h ../include/suit6.h ../include/ranks8.h ../include/suit5.h 
dist12_9_2_2.o: ../include/types.h ../include/suit2.h ../include/suit2.h ../include/suit12.h ../include/ranks9.h 
dist13_9_2_1.o: ../include/types.h ../include/suit13.h ../include/ranks9.h ../include/suit2.h ../include/suit1.h 
dist12_8_3_2.o: ../include/types.h ../include/suit12.h ../include/ranks8.h ../include/suit3.h ../include/suit2.h 
dist12_7_3_3.o: ../include/types.h ../include/suit3.h ../include/suit3.h ../include/suit12.h ../include/ranks7.h 
dist13_8_3_1.o: ../include/types.h ../include/suit13.h ../include/ranks8.h ../include/suit3.h ../include/suit1.h 
dist9_9_5_2.o: ../include/types.h ../include/suit9.h ../include/suit9.h ../include/ranks5.h ../include/suit2.h 
dist8_8_6_3.o: ../include/types.h ../include/suit8.h ../include/suit8.h ../include/ranks6.h ../include/suit3.h 
dist11_10_2_2.o: ../include/types.h ../include/suit2.h ../include/suit2.h ../include/suit11.h ../include/ranks10.h 
dist11_7_4_3.o: ../include/types.h ../include/suit11.h ../include/ranks7.h ../include/suit4.h ../include/suit3.h 
dist8_7_7_3.o: ../include/types.h ../include/suit7.h ../include/suit7.h ../include/ranks8.h ../include/suit3.h 
dist10_10_3_2.o: ../include/types.h ../include/suit10.h ../include/suit10.h ../include/ranks3.h ../include/suit2.h 
dist12_5_4_4.o: ../include/types.h ../include/suit4.h ../include/suit4.h ../include/suit12.h ../include/ranks5.h 
dist10_7_6_2.o: ../include/types.h ../include/suit10.h ../include/ranks7.h ../include/suit6.h ../include/suit2.h 
dist9_8_8_0.o: ../include/types.h ../include/ranks9.h ../include/suit8.h ../include/suit8.h 
dist13_6_4_2.o: ../include/types.h ../include/suit13.h ../include/ranks6.h ../include/suit4.h ../include/suit2.h 
dist9_9_6_1.o: ../include/types.h ../include/suit9.h ../include/suit9.h ../include/ranks6.h ../include/suit1.h 
dist10_6_6_3.o: ../include/types.h ../include/suit6.h ../include/suit6.h ../include/ranks10.h ../include/suit3.h 
dist13_5_5_2.o: ../include/types.h ../include/suit5.h ../include/suit5.h ../include/suit13.h ../include/ranks2.h 
dist13_5_4_3.o: ../include/types.h ../include/suit13.h ../include/ranks5.h ../include/suit4.h ../include/suit3.h 
dist11_9_4_1.o: ../include/types.h ../include/suit11.h ../include/ranks9.h ../include/suit4.h ../include/suit1.h 
dist10_7_5_3.o: ../include/types.h ../include/suit10.h ../include/ranks7.h ../include/suit5.h ../include/suit3.h 
dist11_10_4_0.o: ../include/types.h ../include/suit11.h ../include/suit10.h ../include/ranks4.h 
dist8_7_5_5.o: ../include/types.h ../include/suit5.h ../include/suit5.h ../include/suit8.h ../include/ranks7.h 
dist10_9_3_3.o: ../include/types.h ../include/suit3.h ../include/suit3.h ../include/suit10.h ../include/ranks9.h 
dist11_9_5_0.o: ../include/types.h ../include/suit11.h ../include/ranks9.h ../include/suit5.h 
dist10_8_4_3.o: ../include/types.h ../include/suit10.h ../include/ranks8.h ../include/suit4.h ../include/suit3.h 
dist10_9_6_0.o: ../include/types.h ../include/suit10.h ../include/suit9.h ../include/ranks6.h 
