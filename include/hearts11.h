typedef Card Hearts[11];

int END1 = 77;

Hearts hearts[78] = {
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{12, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{11, 1},{12, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{11, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{10, 1},{11, 1},{12, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{10, 1},{11, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{10, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{9, 1},{10, 1},{11, 1},{12, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{9, 1},{10, 1},{11, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{9, 1},{10, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{9, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{8, 1},{9, 1},{10, 1},{11, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{8, 1},{9, 1},{10, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{8, 1},{9, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{8, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{7, 1},{8, 1},{9, 1},{10, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{7, 1},{8, 1},{9, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{7, 1},{8, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{7, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{5, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{6, 1},{7, 1},{8, 1},{9, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{6, 1},{7, 1},{8, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{6, 1},{7, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{6, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{4, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},},
  {{1, 1},{2, 1},{3, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{5, 1},{6, 1},{7, 1},{8, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{5, 1},{6, 1},{7, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{5, 1},{6, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{5, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{3, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},},
  {{1, 1},{2, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{13, 1},},
  {{1, 1},{2, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{4, 1},{5, 1},{6, 1},{7, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{4, 1},{5, 1},{6, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{4, 1},{5, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{4, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{2, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},},
  {{1, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{13, 1},},
  {{1, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{12, 1},{13, 1},},
  {{1, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{3, 1},{4, 1},{5, 1},{6, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{3, 1},{4, 1},{5, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{3, 1},{4, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{3, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{1, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},},
  {{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{13, 1},},
  {{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{12, 1},{13, 1},},
  {{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{11, 1},{12, 1},{13, 1},},
  {{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{2, 1},{3, 1},{4, 1},{5, 1},{6, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{2, 1},{3, 1},{4, 1},{5, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{2, 1},{3, 1},{4, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{2, 1},{3, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{2, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
  {{3, 1},{4, 1},{5, 1},{6, 1},{7, 1},{8, 1},{9, 1},{10, 1},{11, 1},{12, 1},{13, 1},},
};