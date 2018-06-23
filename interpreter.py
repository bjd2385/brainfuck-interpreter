#! /usr/bin/env python
# -*- coding: utf-8 -*-

"""
A simple Brainfuck interpreter written in Python 3.6 with Dave Beazley's ply
package.
"""

from sly import Lexer, Parser
from sly.lex import Token
from argparse import ArgumentParser
from array import array


def interpreter(program: str) -> None:
    """
    Interpreter implementation for brainfuck using ply.
    """

    # Define the lexer

    class BFLexer(Lexer):
        # Regex for matching each token from the program string
        RCARROT  = r'\>'
        LCARROT  = r'\<'
        INC      = r'\+'
        DEC      = r'\-'
        LBRACKET = r'\]'
        RBRACKET = r'\['
        INPUT    = r','
        OUTPUT   = r'\.'

        # Tokens for brainfuck
        tokens = { RCARROT, LCARROT, INC, DEC, 
                   LBRACKET, RBRACKET, INPUT, OUTPUT }

        ignore = ' \t'

        ignore_newline = r'(\n|[^\>\<\+\-\]\[\,\.].*\r?\n)'

    
    memory_space = array('b', [0] * 30000)


    class BFParser(Parser):
        tokens = BFLexer.tokens

        def __init__(self) -> None:
            self.names = {}

        @_('RCARROT')
        def command(self, p: Parser) -> None:
            return p.expr

        @_('LCARROT')
        def command(self, p: Parser) -> None:
            return p.expr

        @_('INC')
        def command(self, p: Parser) -> None:
            return p.expr

        @_('DEC')
        def command(self, p: Parser) -> None:
            return p.expr

        @_('LBRACKET')
        def command(self, p: Parser) -> None:
            return p.expr

        @_('RBRACKET')
        def command(self, p: Parser) -> None:
            return p.expr

        @_('INPUT')
        def command(self, p: Parser) -> None:
            return p.expr

        @_('OUTPUT')
        def command(self, p: Parser) -> None:
            return p.expr

    
    lexer = BFLexer()

    for token in lexer.tokenize(program):
        print(token)


def arguments() -> None:
    """
    If this program is being used as a commandline tool (as I use it), parse
    the arguments and pass the program to the interpreter.
    """
    arg_parser = ArgumentParser(description=__doc__)

    group = arg_parser.add_mutually_exclusive_group(required=True)

    group.add_argument('-i', '--input', type=str, 
        help='Input string from the terminal'
    )

    group.add_argument('-f', '--file', type=str,
        help='File containing your brainfuck program'
    )

    args = arg_parser.parse_args()

    if args.input:
        interpreter(args.input)
    elif args.file:
        try:
            with open(args.file, 'r') as file:
                programString = file.read()
            interpreter(programString)
        except FileNotFoundError:
            print(f'** File {args.file} was not found, exiting')


if __name__ == '__main__':
    arguments()
