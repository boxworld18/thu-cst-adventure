from add import add

def test_add():
    assert 2 + 2 == add(2, 2)
    assert 2 + 3 == add(2, 3)
