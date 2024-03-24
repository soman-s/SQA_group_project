import pytest
import sys
sys.path.append('..')

import utils


def test_calculate_area():
    # Test case 1: Test with positive numbers
    result = utils.calculate_area(5, 10)
    assert result == 50

    # Test case 2: Test with zero width
    with pytest.raises(ValueError):
        utils.calculate_area(5, 0)

    # Test case 3: Test with negative length
    with pytest.raises(ValueError):
        utils.calculate_area(-5, 10)


if __name__ == "__main__":
    pytest.main()
