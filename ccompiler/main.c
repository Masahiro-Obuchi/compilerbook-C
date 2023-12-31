#include "9cc.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません。\n");
    return 1;
  }

  // トークナイズしてパースする
  // 結果はcodeに保存される
  user_input = argv[1];
  token = tokenize();
  program();

  // アセンブリの前半部分を出力
  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  // プロローグ
  // 変数26個分の領域を確保する
  printf("    push rbp\n");
  printf("    mov rbp, rsp\n");
  printf("    sub rsp, 208\n"); // 26 * 8

  for (int i = 0; code[i]; i++) {
    gen(code[i]);

    // 式の評価結果としてスタックに一つの値が残っているはずなので
    // スタックが溢れないようにポップしておく
    printf("    pop rax\n");
  }

  // エピローグ
  printf("    mov rsp, rbp\n");
  printf("    pop rbp\n");
  printf("    ret\n");
  return 0;
}
