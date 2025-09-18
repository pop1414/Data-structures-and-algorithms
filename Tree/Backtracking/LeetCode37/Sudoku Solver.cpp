#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    // 记录每行已经出现的数字
    vector<unordered_set<char>> rows;
    // 记录每列已经出现的数字
    vector<unordered_set<char>> cols;
    // 记录每个九宫格已经出现的数字
    vector<unordered_set<char>> boxes;

    void solveSudoku(vector<vector<char>>& board) {

        // ★ 关键：先分配大小
        rows.assign(9, {});
        cols.assign(9, {});
        boxes.assign(9, {});

        // 将预设数字加入集合
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    rows[i].insert(board[i][j]);
                    cols[j].insert(board[i][j]);
                    boxes[getBoxIndex(i, j)].insert(board[i][j]);
                }
            }
        }
       backtrack(board, 0, 0);
    }

    bool backtrack(vector<vector<char>>& board, int curI, int curJ){
         for(int i = curI; i < 9; i++){
            int jStart = (i == curI ? curJ : 0);// 容易错的，当i变成下一行的时候，j就要从0开始
            for(int j = jStart; j < 9; j++){
                if(board[i][j] == '.'){
                    for(char num = '1'; num <= '9'; num++){
                    
                        if (isValid(i, j, num)){
                            board[i][j] = num;
                            rows[i].insert(num);
                            cols[j].insert(num);
                            boxes[getBoxIndex(i, j)].insert(num);

                            if (backtrack(board, i, j))  return true;

                            board[i][j] = '.';
                            rows[i].erase(num);
                            cols[j].erase(num);
                            boxes[getBoxIndex(i, j)].erase(num);
                        }
                    }

                        
                    return false;
                }
            }
        }
        return true;
    }

    // 获取 (r, c) 所在的九宫格索引
    int getBoxIndex(int r, int c) {
        return (r / 3) * 3 + (c / 3);
    }


    // bool isValid(vector<vector<char>>& board, int r, int c){
    //     unordered_map<int, int> row;// <num, count>
    //     unordered_map<int, int> col;
    //     unordered_map<int, int> box;
    //     for(int j = 0; j < 9; j++){
    //         if(board[r][j] == '.') continue;
    //         if(row.count(board[r][j])){
    //             return false;
    //         }
    //         row[board[r][j]] = 1;
    //     }
    //     for(int i = 0; i < 9; i++){
    //         if(board[i][c] == '.') continue;
    //         if(col.count(board[i][c])){
    //             return false;
    //         }
    //         col[board[i][c]] = 1;
    //     }
    //     int x = r / 3 * 3;
    //     int y = c / 3 * 3;
    //     for(int i = x; i < x + 3; i++){
    //         for(int j = y; j < y + 3; j++){
    //             if(board[i][j] == '.') continue;
    //             if(box.count(board[i][j])){
    //                 return false;
    //             }
    //             box[board[i][j]] = 1;
    //         }
    //     }
    //     return true;
    // }

    // 判断是否可以在 (r, c) 位置放置数字 num
    bool isValid(int r, int c, char num) {
        // 现在只需要查询三次哈希表即可
        if (rows[r].count(num)) return false;
        if (cols[c].count(num)) return false;
        if (boxes[getBoxIndex(r, c)].count(num)) return false;
        return true;
    }

};

