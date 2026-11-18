/* ex113_file_count.c —— 统计文件：行数、字符数、单词数
 *
 * 要求：
 *   1. 让自己的程序先写一个测试文件 test113.txt，内容固定三行：
 *        hello world
 *        C programming 2026
 *        file io is easy
 *   2. 用 fgetc 逐字符读，统计：行数、字符数、单词数
 *   3. 输出三个数字
 *
 * 预期输出：
 *   行 3  字符 47  单词 9
 *
 * 要点：
 *   - fgetc 返回 int（不是 char），因为要能表示 EOF（-1）
 *   - 单词统计用 inWord 标记：连续空格只算一次
 *   - 行数用 '\n' 的个数统计
 */

#include <stdio.h>

int main(void)
{
    const char *path = "test113.txt";

    /* TODO 1：写测试文件（3 行，注意每行末尾要有 \n） */
	
	FILE *out = fopen(path, "w");
	if (out == NULL) {
		perror("fopen");
		return 1;
	}
	fprintf(out, "hello world\n");
	fprintf(out, "C programming 2026\n");
	fprintf(out, "file io is easy\n");
	fclose(out);
    /* TODO 2：用 "r" 打开，fgetc 循环统计 */
	FILE *in = fopen(path, "r");
	if (in == NULL) {
		perror("fopen");
		return 1;
	}
	int lines = 0, words = 0, word = 0, inWord = 0;
	int chars = 0;
	while ((word = fgetc(in)) != EOF) {
		++chars;
		if (word == '\n') {
			++lines;
		}
		if (word == ' ' || word == '\n' || word == '\t') {
			inWord = 0;
		}
		else if(!inWord) {
			inWord = 1;
			++words;
		}
	}
	fclose(in);
    /* TODO 3：输出 行 / 字符 / 单词 */
	printf("预期输出：\n");
	printf("行 %d ", lines);
	printf("字符 %d ", chars);
	printf("单词 %d\n", words);
    return 0;
}
