def recursive_distance():

    # base case
    # first row and first column
    matrix[0][0] = (0, None)

    # first column
    for n in range(1, len(a) + 1):
        matrix[n][0] = (n, Operation.DELETED)

    # first row
    for n in range(1, len(b) + 1):
        matrix[0][n] = (n, Operation.INSERTED)
