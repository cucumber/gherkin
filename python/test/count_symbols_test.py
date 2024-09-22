# coding=utf-8


def test_count_length_of_astral_point_symbols_correctly():
    string = "\U0001f63b"
    assert 1 == len(string)


def test_count_length_of_ascii_symbols_correctly():
    string = "hello"
    assert 5 == len(string)


def test_count_length_of_latin_symbols_correctly():
    string = "Scénario"
    assert 8, len(string)
