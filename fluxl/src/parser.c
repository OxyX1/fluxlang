#include "../include/parser.h"
#include <stdio.h>
#include <string.h>

void init_parser(Parser *parser, const char *source) {
    parser->source = source;
    parser->position = 0;
    advance(parser);
}

void advance(Parser *parser) {
    parser->current_token = get_next_token(&parser->source);
}

ASTNode* parse(Parser *parser) {
    ASTNode *root = NULL;
    
    while (parser->current_token.type != TOKEN_EOF) {
        if (parser->current_token.type == TOKEN_KEYWORD) {
            if (strcmp(parser->current_token.value, "mod") == 0) {
                advance(parser); // Skip 'mod'
                if (parser->current_token.type == TOKEN_STRING) {
                    ASTNode *mod_node = create_ast_node(AST_MOD, parser->current_token.value);
                    root = mod_node;
                    advance(parser);
                }
            }
            else if (strcmp(parser->current_token.value, "return") == 0) {
                advance(parser); // Skip 'return'
                if (parser->current_token.type == TOKEN_NUMBER) {
                    ASTNode *return_node = create_ast_node(AST_RETURN, parser->current_token.value);
                    root = return_node;
                    advance(parser);
                    if (parser->current_token.type == TOKEN_SYMBOL && parser->current_token.value[0] == ';') {
                        advance(parser); // Skip ';'
                    } else {
                        printf("Error: expected ';' after return value\n");
                        return NULL;
                    }
                } else {
                    printf("Error: expected number after return\n");
                    return NULL;
                }
            }
            else {
                // Handle other keywords or errors
                advance(parser);
            }
        } else if (parser->current_token.type == TOKEN_IDENTIFIER) {
            // Handle function or variable declarations (if needed)
            ASTNode *identifier_node = create_ast_node(AST_IDENTIFIER, parser->current_token.value);
            root = identifier_node;
            advance(parser);
        } else if (parser->current_token.type == TOKEN_NUMBER) {
            ASTNode *number_node = create_ast_node(AST_NUMBER, parser->current_token.value);
            root = number_node;
            advance(parser);
        } else {
            // Handle unknown tokens
            printf("Unknown token: %s\n", parser->current_token.value);
            advance(parser);
        }
    }

    return root;
}
