import numpy as np

in_path = "../inputData/in"
out_path = "../outputData/control/controlM"

dimensions = [10, 100, 200, 300, 400, 500, 600, 700,
              800, 900, 1000, 1500, 2000, 2500, 3000, 3500, 4000]


def main():
    for dim in dimensions:
        path_to_in_file = in_path + str(dim) + ".txt"
        a, b = read_matrices_from_file(path_to_in_file, dim)
        c = a @ b

        path_to_out_file = out_path + str(dim) + ".txt"
        write_result_to_file(path_to_out_file, c, dim)


def write_result_to_file(out_file_string, matrix, dimension):
    """Writes a result matrice to a file for comparison"""

    with open(out_file_string, 'w') as f:
        f.write(str(dimension))
        f.write('\n')
        for i in range(dimension):
            for j in range(dimension):
                f.write(str(matrix[i][j]))
                f.write('\n')


def read_matrices_from_file(file_string, dim):
    """Reads the matrices from a specified file.
    Returns two matrices A and B"""

    with open(file_string, 'r') as f:
        x = f.readline()
        a = np.zeros((dim, dim), dtype=int)
        b = np.zeros((dim, dim), dtype=int)

        for i in range(dim):
            for j in range(dim):
                a[i][j] = f.readline()

        for i in range(dim):
            for j in range(dim):
                b[i][j] = f.readline()

    return (a, b)


if __name__ == "__main__":
    main()
