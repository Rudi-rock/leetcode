import java.util.*;

class Solution {

    public int minMoves(String[] classroom, int energy) {
        int m = classroom.length;
        int n = classroom[0].length();

        int sr = 0, sc = 0;
        List<int[]> litter = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char cell = classroom[i].charAt(j);

                if (cell == 'S') {
                    sr = i;
                    sc = j;
                } else if (cell == 'L') {
                    litter.add(new int[]{i, j});
                }
            }
        }

        int k = litter.size();

        if (k == 0) return 0;

        int[][] litterId = new int[m][n];
        for (int[] row : litterId) {
            Arrays.fill(row, -1);
        }

        for (int i = 0; i < k; i++) {
            int[] pos = litter.get(i);
            litterId[pos[0]][pos[1]] = i;
        }

        int fullMask = (1 << k) - 1;

        boolean[][][][] visited =
                new boolean[m][n][1 << k][energy + 1];

        Queue<int[]> queue = new LinkedList<>();

        queue.offer(new int[]{sr, sc, 0, energy});
        visited[sr][sc][0][energy] = true;

        int moves = 0;

        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        while (!queue.isEmpty()) {
            int size = queue.size();

            while (size-- > 0) {
                int[] current = queue.poll();

                int r = current[0];
                int c = current[1];
                int mask = current[2];
                int remainingEnergy = current[3];

                if (mask == fullMask) {
                    return moves;
                }

                if (remainingEnergy == 0) continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n
                            || classroom[nr].charAt(nc) == 'X') {
                        continue;
                    }

                    int newEnergy = remainingEnergy - 1;
                    int newMask = mask;

                    if (litterId[nr][nc] != -1) {
                        newMask |= (1 << litterId[nr][nc]);
                    }

                    if (classroom[nr].charAt(nc) == 'R') {
                        newEnergy = energy;
                    }

                    if (!visited[nr][nc][newMask][newEnergy]) {
                        visited[nr][nc][newMask][newEnergy] = true;
                        queue.offer(new int[]{
                                nr, nc, newMask, newEnergy
                        });
                    }
                }
            }

            moves++;
        }

        return -1;
    }
}
