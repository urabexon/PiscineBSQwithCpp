/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirokiurabe <hirokiurabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:09:44 by hirokiurabe       #+#    #+#             */
/*   Updated: 2025/02/10 23:22:34 by hirokiurabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.hpp"
using namespace std;

// 数字かチェックする関数
static bool is_valid_number(const string &s) {
    if (s.empty())
        return false;
    for (char c : s) {
        if (!isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

// istreamから読み取った1つのマップを処理する
static bool processMap(istream &in) {
    string header;
    if (!getline(in, header)) {
        cerr << "map error" << endl;
        return false;
    }
    if (header.size() < 4) {
        cerr << "map error" << endl;
        return false;
    }
    // ヘッダーの末尾3文字がそれぞれempty, obstacle, fullの文字
    char empty_char    = header[header.size() - 3];
    char obstacle_char = header[header.size() - 2];
    char full_char     = header[header.size() - 1];
    // 3文字が全て異なるかチェック
    if (empty_char == obstacle_char || empty_char == full_char || obstacle_char == full_char) {
        cerr << "map error" << endl;
        return false;
    }
    // ヘッダーの最初の部分は行数を表す数字
    string rows_str = header.substr(0, header.size() - 3);
    if (!is_valid_number(rows_str)) {
        cerr << "map error" << endl;
        return false;
    }
    int row_count = 0;
    try {
        row_count = stoi(rows_str);
    } catch (...) {
        cerr << "map error" << endl;
        return false;
    }
    if (row_count <= 0) {
        cerr << "map error" << endl;
        return false;
    }
    // マップの各行を読み込む
    vector<string> map_lines;
    string line;
    for (int i = 0; i < row_count; i++) {
        if (!getline(in, line)) {
            cerr << "map error" << endl;
            return false;
        }
        map_lines.push_back(line);
    }
    // 余分な行があればエラー
    if (getline(in, line)) {
        if (!line.empty()) {
            cerr << "map error" << endl;
            return false;
        }
        while (getline(in, line)) {
            if(!line.empty()) {
                cerr << "map error" << endl;
                return false;
            }
        }
    }
    // 各行の長さが同じ、かつ1文字以上あるか確認する
    if (map_lines.empty()) {
        cerr << "map error" << endl;
        return false;
    }
    size_t col_count = map_lines[0].size();
    if (col_count == 0) {
        cerr << "map error" << endl;
        return false;
    }
    // 各行の長さが同じ+使われている文字がempty_char、obstacle_charのみか確認
    for (const auto &row : map_lines) {
        if (row.size() != col_count) {
            cerr << "map error" << endl;
            return false;
        }
        for (char c : row) {
            if (c != empty_char && c != obstacle_char) {
                cerr << "map error" << endl;
                return false;
            }
        }
    }
    // DP(動的計画法)でempty_char のみで構成される最大の正方形を探索する
    // ([i][j]：マップ[i][j]を右下端とする正方形の最大の辺の長さ)
    vector<vector<int>> dp(map_lines.size(), vector<int>(col_count, 0));
    int max_size = 0;
    int best_top = 0;
    int best_left = 0;
    for (size_t i = 0; i < map_lines.size(); i++) {
        for (size_t j = 0; j < col_count; j++) {
            if (map_lines[i][j] == obstacle_char) {
                dp[i][j] = 0;
            } else {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                dp[i][j] = min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] }) + 1;
            }
            // サイズが大きい場合、または同じサイズの場合は上と左を優先して更新
            if (dp[i][j] > max_size) {
                max_size = dp[i][j];
                best_top = i - dp[i][j] + 1;
                best_left = j - dp[i][j] + 1;
            } else if (dp[i][j] == max_size && max_size > 0) {
                int candidate_top = i - dp[i][j] + 1;
                int candidate_left = j - dp[i][j] + 1;
                if (candidate_top < best_top || (candidate_top == best_top && candidate_left < best_left)) {
                    best_top = candidate_top;
                    best_left = candidate_left;
                }
            }
        }
    }
    // 最大正方形の領域をfull_charに置き換える
    if (max_size > 0) {
        for (int i = best_top; i < best_top + max_size; i++) {
            for (int j = best_left; j < best_left + max_size; j++)
                map_lines[i][j] = full_char;
        }
    }
    // 解答マップを出力
    for (const auto &row : map_lines)
        cout << row << endl;
    return true;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        processMap(cin);
    } else {
        // 指定した各ファイルを順に処理する
        for (int i = 1; i < argc; i++) {
            ifstream file(argv[i]);
            if (!file.is_open()) {
                cerr << "map error" << endl;
            } else {
                processMap(file);
            }
            // 複数マップを改行で区切るために必要
            if (i < argc - 1)
                cout << endl;
        }
    }
    return 0;
}
