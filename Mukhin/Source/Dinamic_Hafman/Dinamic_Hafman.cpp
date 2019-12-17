#include "tree.h"

int use_dinamic(std::string argv) {
    char c = '1';
    Tree coding_tree;
    std::stringstream ss;
    ss << argv;
    std::ofstream code_message(std::string("code_message_Dinamic_Hafman.txt"));
    std::ofstream decode_message(std::string("decode_message_Dinamic_Hafman.txt"));

    while (ss.peek() != EOF) {
        ss.get(c);
        coding_tree.insert(c);
        std::vector<std::pair<int, std::shared_ptr<Node>>> tmp = coding_tree.get_order();

        while (!coding_tree.check_ascending(tmp)) {
            coding_tree.restructure();
            tmp = coding_tree.get_order();
        }
    }

    code_message << coding_tree.code_string;
    code_message.close();

    coding_tree.decode();

    decode_message << coding_tree.decode_string;
    decode_message.close();
    return 0;
}
