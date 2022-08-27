typedef struct {
  unsigned char rank;
  unsigned char suit;
} Card;

typedef Card Spades[3];

int END0 = 285;

Spades spades[286] = {
  {{1, 0},{2, 0},{3, 0},},
  {{1, 0},{2, 0},{4, 0},},
  {{1, 0},{2, 0},{5, 0},},
  {{1, 0},{2, 0},{6, 0},},
  {{1, 0},{2, 0},{7, 0},},
  {{1, 0},{2, 0},{8, 0},},
  {{1, 0},{2, 0},{9, 0},},
  {{1, 0},{2, 0},{10, 0},},
  {{1, 0},{2, 0},{11, 0},},
  {{1, 0},{2, 0},{12, 0},},
  {{1, 0},{2, 0},{13, 0},},
  {{1, 0},{3, 0},{4, 0},},
  {{1, 0},{3, 0},{5, 0},},
  {{1, 0},{3, 0},{6, 0},},
  {{1, 0},{3, 0},{7, 0},},
  {{1, 0},{3, 0},{8, 0},},
  {{1, 0},{3, 0},{9, 0},},
  {{1, 0},{3, 0},{10, 0},},
  {{1, 0},{3, 0},{11, 0},},
  {{1, 0},{3, 0},{12, 0},},
  {{1, 0},{3, 0},{13, 0},},
  {{1, 0},{4, 0},{5, 0},},
  {{1, 0},{4, 0},{6, 0},},
  {{1, 0},{4, 0},{7, 0},},
  {{1, 0},{4, 0},{8, 0},},
  {{1, 0},{4, 0},{9, 0},},
  {{1, 0},{4, 0},{10, 0},},
  {{1, 0},{4, 0},{11, 0},},
  {{1, 0},{4, 0},{12, 0},},
  {{1, 0},{4, 0},{13, 0},},
  {{1, 0},{5, 0},{6, 0},},
  {{1, 0},{5, 0},{7, 0},},
  {{1, 0},{5, 0},{8, 0},},
  {{1, 0},{5, 0},{9, 0},},
  {{1, 0},{5, 0},{10, 0},},
  {{1, 0},{5, 0},{11, 0},},
  {{1, 0},{5, 0},{12, 0},},
  {{1, 0},{5, 0},{13, 0},},
  {{1, 0},{6, 0},{7, 0},},
  {{1, 0},{6, 0},{8, 0},},
  {{1, 0},{6, 0},{9, 0},},
  {{1, 0},{6, 0},{10, 0},},
  {{1, 0},{6, 0},{11, 0},},
  {{1, 0},{6, 0},{12, 0},},
  {{1, 0},{6, 0},{13, 0},},
  {{1, 0},{7, 0},{8, 0},},
  {{1, 0},{7, 0},{9, 0},},
  {{1, 0},{7, 0},{10, 0},},
  {{1, 0},{7, 0},{11, 0},},
  {{1, 0},{7, 0},{12, 0},},
  {{1, 0},{7, 0},{13, 0},},
  {{1, 0},{8, 0},{9, 0},},
  {{1, 0},{8, 0},{10, 0},},
  {{1, 0},{8, 0},{11, 0},},
  {{1, 0},{8, 0},{12, 0},},
  {{1, 0},{8, 0},{13, 0},},
  {{1, 0},{9, 0},{10, 0},},
  {{1, 0},{9, 0},{11, 0},},
  {{1, 0},{9, 0},{12, 0},},
  {{1, 0},{9, 0},{13, 0},},
  {{1, 0},{10, 0},{11, 0},},
  {{1, 0},{10, 0},{12, 0},},
  {{1, 0},{10, 0},{13, 0},},
  {{1, 0},{11, 0},{12, 0},},
  {{1, 0},{11, 0},{13, 0},},
  {{1, 0},{12, 0},{13, 0},},
  {{2, 0},{3, 0},{4, 0},},
  {{2, 0},{3, 0},{5, 0},},
  {{2, 0},{3, 0},{6, 0},},
  {{2, 0},{3, 0},{7, 0},},
  {{2, 0},{3, 0},{8, 0},},
  {{2, 0},{3, 0},{9, 0},},
  {{2, 0},{3, 0},{10, 0},},
  {{2, 0},{3, 0},{11, 0},},
  {{2, 0},{3, 0},{12, 0},},
  {{2, 0},{3, 0},{13, 0},},
  {{2, 0},{4, 0},{5, 0},},
  {{2, 0},{4, 0},{6, 0},},
  {{2, 0},{4, 0},{7, 0},},
  {{2, 0},{4, 0},{8, 0},},
  {{2, 0},{4, 0},{9, 0},},
  {{2, 0},{4, 0},{10, 0},},
  {{2, 0},{4, 0},{11, 0},},
  {{2, 0},{4, 0},{12, 0},},
  {{2, 0},{4, 0},{13, 0},},
  {{2, 0},{5, 0},{6, 0},},
  {{2, 0},{5, 0},{7, 0},},
  {{2, 0},{5, 0},{8, 0},},
  {{2, 0},{5, 0},{9, 0},},
  {{2, 0},{5, 0},{10, 0},},
  {{2, 0},{5, 0},{11, 0},},
  {{2, 0},{5, 0},{12, 0},},
  {{2, 0},{5, 0},{13, 0},},
  {{2, 0},{6, 0},{7, 0},},
  {{2, 0},{6, 0},{8, 0},},
  {{2, 0},{6, 0},{9, 0},},
  {{2, 0},{6, 0},{10, 0},},
  {{2, 0},{6, 0},{11, 0},},
  {{2, 0},{6, 0},{12, 0},},
  {{2, 0},{6, 0},{13, 0},},
  {{2, 0},{7, 0},{8, 0},},
  {{2, 0},{7, 0},{9, 0},},
  {{2, 0},{7, 0},{10, 0},},
  {{2, 0},{7, 0},{11, 0},},
  {{2, 0},{7, 0},{12, 0},},
  {{2, 0},{7, 0},{13, 0},},
  {{2, 0},{8, 0},{9, 0},},
  {{2, 0},{8, 0},{10, 0},},
  {{2, 0},{8, 0},{11, 0},},
  {{2, 0},{8, 0},{12, 0},},
  {{2, 0},{8, 0},{13, 0},},
  {{2, 0},{9, 0},{10, 0},},
  {{2, 0},{9, 0},{11, 0},},
  {{2, 0},{9, 0},{12, 0},},
  {{2, 0},{9, 0},{13, 0},},
  {{2, 0},{10, 0},{11, 0},},
  {{2, 0},{10, 0},{12, 0},},
  {{2, 0},{10, 0},{13, 0},},
  {{2, 0},{11, 0},{12, 0},},
  {{2, 0},{11, 0},{13, 0},},
  {{2, 0},{12, 0},{13, 0},},
  {{3, 0},{4, 0},{5, 0},},
  {{3, 0},{4, 0},{6, 0},},
  {{3, 0},{4, 0},{7, 0},},
  {{3, 0},{4, 0},{8, 0},},
  {{3, 0},{4, 0},{9, 0},},
  {{3, 0},{4, 0},{10, 0},},
  {{3, 0},{4, 0},{11, 0},},
  {{3, 0},{4, 0},{12, 0},},
  {{3, 0},{4, 0},{13, 0},},
  {{3, 0},{5, 0},{6, 0},},
  {{3, 0},{5, 0},{7, 0},},
  {{3, 0},{5, 0},{8, 0},},
  {{3, 0},{5, 0},{9, 0},},
  {{3, 0},{5, 0},{10, 0},},
  {{3, 0},{5, 0},{11, 0},},
  {{3, 0},{5, 0},{12, 0},},
  {{3, 0},{5, 0},{13, 0},},
  {{3, 0},{6, 0},{7, 0},},
  {{3, 0},{6, 0},{8, 0},},
  {{3, 0},{6, 0},{9, 0},},
  {{3, 0},{6, 0},{10, 0},},
  {{3, 0},{6, 0},{11, 0},},
  {{3, 0},{6, 0},{12, 0},},
  {{3, 0},{6, 0},{13, 0},},
  {{3, 0},{7, 0},{8, 0},},
  {{3, 0},{7, 0},{9, 0},},
  {{3, 0},{7, 0},{10, 0},},
  {{3, 0},{7, 0},{11, 0},},
  {{3, 0},{7, 0},{12, 0},},
  {{3, 0},{7, 0},{13, 0},},
  {{3, 0},{8, 0},{9, 0},},
  {{3, 0},{8, 0},{10, 0},},
  {{3, 0},{8, 0},{11, 0},},
  {{3, 0},{8, 0},{12, 0},},
  {{3, 0},{8, 0},{13, 0},},
  {{3, 0},{9, 0},{10, 0},},
  {{3, 0},{9, 0},{11, 0},},
  {{3, 0},{9, 0},{12, 0},},
  {{3, 0},{9, 0},{13, 0},},
  {{3, 0},{10, 0},{11, 0},},
  {{3, 0},{10, 0},{12, 0},},
  {{3, 0},{10, 0},{13, 0},},
  {{3, 0},{11, 0},{12, 0},},
  {{3, 0},{11, 0},{13, 0},},
  {{3, 0},{12, 0},{13, 0},},
  {{4, 0},{5, 0},{6, 0},},
  {{4, 0},{5, 0},{7, 0},},
  {{4, 0},{5, 0},{8, 0},},
  {{4, 0},{5, 0},{9, 0},},
  {{4, 0},{5, 0},{10, 0},},
  {{4, 0},{5, 0},{11, 0},},
  {{4, 0},{5, 0},{12, 0},},
  {{4, 0},{5, 0},{13, 0},},
  {{4, 0},{6, 0},{7, 0},},
  {{4, 0},{6, 0},{8, 0},},
  {{4, 0},{6, 0},{9, 0},},
  {{4, 0},{6, 0},{10, 0},},
  {{4, 0},{6, 0},{11, 0},},
  {{4, 0},{6, 0},{12, 0},},
  {{4, 0},{6, 0},{13, 0},},
  {{4, 0},{7, 0},{8, 0},},
  {{4, 0},{7, 0},{9, 0},},
  {{4, 0},{7, 0},{10, 0},},
  {{4, 0},{7, 0},{11, 0},},
  {{4, 0},{7, 0},{12, 0},},
  {{4, 0},{7, 0},{13, 0},},
  {{4, 0},{8, 0},{9, 0},},
  {{4, 0},{8, 0},{10, 0},},
  {{4, 0},{8, 0},{11, 0},},
  {{4, 0},{8, 0},{12, 0},},
  {{4, 0},{8, 0},{13, 0},},
  {{4, 0},{9, 0},{10, 0},},
  {{4, 0},{9, 0},{11, 0},},
  {{4, 0},{9, 0},{12, 0},},
  {{4, 0},{9, 0},{13, 0},},
  {{4, 0},{10, 0},{11, 0},},
  {{4, 0},{10, 0},{12, 0},},
  {{4, 0},{10, 0},{13, 0},},
  {{4, 0},{11, 0},{12, 0},},
  {{4, 0},{11, 0},{13, 0},},
  {{4, 0},{12, 0},{13, 0},},
  {{5, 0},{6, 0},{7, 0},},
  {{5, 0},{6, 0},{8, 0},},
  {{5, 0},{6, 0},{9, 0},},
  {{5, 0},{6, 0},{10, 0},},
  {{5, 0},{6, 0},{11, 0},},
  {{5, 0},{6, 0},{12, 0},},
  {{5, 0},{6, 0},{13, 0},},
  {{5, 0},{7, 0},{8, 0},},
  {{5, 0},{7, 0},{9, 0},},
  {{5, 0},{7, 0},{10, 0},},
  {{5, 0},{7, 0},{11, 0},},
  {{5, 0},{7, 0},{12, 0},},
  {{5, 0},{7, 0},{13, 0},},
  {{5, 0},{8, 0},{9, 0},},
  {{5, 0},{8, 0},{10, 0},},
  {{5, 0},{8, 0},{11, 0},},
  {{5, 0},{8, 0},{12, 0},},
  {{5, 0},{8, 0},{13, 0},},
  {{5, 0},{9, 0},{10, 0},},
  {{5, 0},{9, 0},{11, 0},},
  {{5, 0},{9, 0},{12, 0},},
  {{5, 0},{9, 0},{13, 0},},
  {{5, 0},{10, 0},{11, 0},},
  {{5, 0},{10, 0},{12, 0},},
  {{5, 0},{10, 0},{13, 0},},
  {{5, 0},{11, 0},{12, 0},},
  {{5, 0},{11, 0},{13, 0},},
  {{5, 0},{12, 0},{13, 0},},
  {{6, 0},{7, 0},{8, 0},},
  {{6, 0},{7, 0},{9, 0},},
  {{6, 0},{7, 0},{10, 0},},
  {{6, 0},{7, 0},{11, 0},},
  {{6, 0},{7, 0},{12, 0},},
  {{6, 0},{7, 0},{13, 0},},
  {{6, 0},{8, 0},{9, 0},},
  {{6, 0},{8, 0},{10, 0},},
  {{6, 0},{8, 0},{11, 0},},
  {{6, 0},{8, 0},{12, 0},},
  {{6, 0},{8, 0},{13, 0},},
  {{6, 0},{9, 0},{10, 0},},
  {{6, 0},{9, 0},{11, 0},},
  {{6, 0},{9, 0},{12, 0},},
  {{6, 0},{9, 0},{13, 0},},
  {{6, 0},{10, 0},{11, 0},},
  {{6, 0},{10, 0},{12, 0},},
  {{6, 0},{10, 0},{13, 0},},
  {{6, 0},{11, 0},{12, 0},},
  {{6, 0},{11, 0},{13, 0},},
  {{6, 0},{12, 0},{13, 0},},
  {{7, 0},{8, 0},{9, 0},},
  {{7, 0},{8, 0},{10, 0},},
  {{7, 0},{8, 0},{11, 0},},
  {{7, 0},{8, 0},{12, 0},},
  {{7, 0},{8, 0},{13, 0},},
  {{7, 0},{9, 0},{10, 0},},
  {{7, 0},{9, 0},{11, 0},},
  {{7, 0},{9, 0},{12, 0},},
  {{7, 0},{9, 0},{13, 0},},
  {{7, 0},{10, 0},{11, 0},},
  {{7, 0},{10, 0},{12, 0},},
  {{7, 0},{10, 0},{13, 0},},
  {{7, 0},{11, 0},{12, 0},},
  {{7, 0},{11, 0},{13, 0},},
  {{7, 0},{12, 0},{13, 0},},
  {{8, 0},{9, 0},{10, 0},},
  {{8, 0},{9, 0},{11, 0},},
  {{8, 0},{9, 0},{12, 0},},
  {{8, 0},{9, 0},{13, 0},},
  {{8, 0},{10, 0},{11, 0},},
  {{8, 0},{10, 0},{12, 0},},
  {{8, 0},{10, 0},{13, 0},},
  {{8, 0},{11, 0},{12, 0},},
  {{8, 0},{11, 0},{13, 0},},
  {{8, 0},{12, 0},{13, 0},},
  {{9, 0},{10, 0},{11, 0},},
  {{9, 0},{10, 0},{12, 0},},
  {{9, 0},{10, 0},{13, 0},},
  {{9, 0},{11, 0},{12, 0},},
  {{9, 0},{11, 0},{13, 0},},
  {{9, 0},{12, 0},{13, 0},},
  {{10, 0},{11, 0},{12, 0},},
  {{10, 0},{11, 0},{13, 0},},
  {{10, 0},{12, 0},{13, 0},},
  {{11, 0},{12, 0},{13, 0},},
};