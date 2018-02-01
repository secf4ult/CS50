from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""

    # set up 2D list
    matrix = [[0 for j in range(len(b) + 1)] for i in range(len(a) + 1)]

    # fill in the other entries
    for i in range(len(a) + 1):
        for j in range(len(b) + 1):
            # base case, first cell
            if i == 0 and j == 0:
                matrix[0][0] = (0, None)
            # first row
            elif i == 0:
                matrix[0][j] = (j, Operation.INSERTED)
            # first column
            elif j == 0:
                matrix[i][0] = (i, Operation.DELETED)
            # remains
            else:
                # cost[i][j] is min of
                # deletion: cost[i - 1][j] + 1
                dele = (matrix[i - 1][j][0] + 1, Operation.DELETED)
                # insertion: cost[i][j - 1] + 1
                inse = (matrix[i][j - 1][0] + 1, Operation.INSERTED)
                # substitution:
                if a[i - 1] == b[j - 1]:
                    # cost[i - 1][j - 1] if i-th char of a is j-th char of b
                    subs = (matrix[i - 1][j - 1][0], Operation.SUBSTITUTED)
                else:
                    # cost[i - 1][j - 1] + 1 otherwise
                    subs = (matrix[i - 1][j - 1][0] + 1, Operation.SUBSTITUTED)

                min_op = min(dele,
                             inse,
                             subs,
                             key=lambda x: x[0])

                matrix[i][j] = min_op

    return matrix
