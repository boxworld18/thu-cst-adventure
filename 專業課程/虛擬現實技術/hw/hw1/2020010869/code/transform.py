import numpy as np


def identity(N):
    """
    Parameters:
    - N (int): size of the identity matrix.
    Return:
    - np.array, identity matrix of size NxN.
    """
    return np.identity(N, dtype=np.float32)
    


def zeros(N):
    """
    Parameters:
    - N (int): size of the zero matrix.
    Return:
    - np.array, zero matrix of size NxN.
    """
    return np.zeros((N, N), dtype=np.float32)


def normalize(v) -> np.array:
    """
    Parameters:
    - v (np.array): vector to be normalized.
    Return:
    - np.array, normalized unit vector.
    """
    return v / np.linalg.norm(v)


def translate(offsets):
    """
    Compute the 4x4 translation matrix.
    Parameters:
    - offsets (list of length 3): translation offsets. offsets[0], offsets[1], offsets[2] are offset on the x, y, z axis respectively.
    Return:
    - np.array, 4x4 translation matrix.
    """
    t_mat = identity(4)
    t_mat[0:3, 3] = offsets
    return t_mat


# -------------------------------------------#
#            Begin Assignment 1              #
# -------------------------------------------#

"""
Useful NumPy operations:
- degrees to radians: np.radians(angle)
- vector dot product: a.dot(b) or np.dot(a, b)
- vector cross product: np.cross(a, b)
- matrix multiplication: np.matmul(a, b) or a @ b
"""

def rotate(angle, axis):
    """
    Compute the 4x4 rotation matrix.
    Parameters:
    - angle (float): rotation angle, in degrees.
    - axis (list of length 3): the axis to rotate about.
    Return:
    - np.array, 4x4 rotation matrix.
    """
    angle = np.radians(angle)
    r_mat = zeros(4)
    r_mat[0, 1] -= axis[2]
    r_mat[0, 2] += axis[1]
    r_mat[1, 0] += axis[2]
    r_mat[1, 2] -= axis[0]
    r_mat[2, 0] -= axis[1]
    r_mat[2, 1] += axis[0]
    r_mat *= np.sin(angle)

    r_mat[0:3, 0:3] += np.cos(angle) * identity(3)
    r_mat[0:3, 0:3] += np.outer(axis, axis) * (1 - np.cos(angle))

    r_mat[3, 3] = 1
    return r_mat


def scale(factors):
    """
    Compute the 4x4 scaling matrix.
    Parameters:
    - factors (list of length 3): scaling factors. factors[0], factors[1], factors[2] are scaling factor for the x, y, z axis respectively.
    Return:
    - np.array, 4x4 scaling matrix.
    """
    s_mat = np.diag(factors + [1])
    return s_mat


def modelTransform(offsets, angles, factors):
    """
    Compute the model transformation matrix by applying transformations in the following order:
    1. scaling
    2. rotation about x(1, 0, 0)
    3. rotation about y(0, 1, 0)
    4. rotation about z(0, 0, 1)
    5. translation
    Call translate, rotate and scale implemented above to get a final model transformation matrix.
    Parameters:
    - offsets (list of length 3): translation offsets. offsets[0], offsets[1], offsets[2] are offset on the x, y, z axis respectively.
    - angles (list of length 3): rotation angles. angles[0], angles[1], angles[2] are rotation angle around the x, y, z axis respectively.
    - factors (list of length 3): scaling factors. factors[0], factors[1], factors[2] are scaling factor for the x, y, z axis respectively.
    Return:
    - np.array, 4x4 model transformation matrix.
    """
    t_mat = scale(factors)
    t_mat = rotate(angles[0], [1, 0, 0]) @ t_mat
    t_mat = rotate(angles[1], [0, 1, 0]) @ t_mat
    t_mat = rotate(angles[2], [0, 0, 1]) @ t_mat
    t_mat = translate(offsets) @ t_mat
    return t_mat


def viewTransform(ori, center, up):
    """
    Compute the view transformation matrix given camera position, look-at point, and up vector.
    We assume the camera looks at -z and up at y in the camera coordinate.
    Parameters:
    - ori (list of length 3): camera position.
    - center (list of length 3): camera look-at point.
    - up (list of length 3): camera up direction.
    Return:
    - np.array, 4x4 view transformation matrix.
    """
    z = normalize(np.array(ori) - np.array(center))
    x = normalize(np.cross(up, z))
    y = np.cross(z, x)
    mat = identity(4)
    mat[0, 0:3] = x
    mat[1, 0:3] = y
    mat[2, 0:3] = z
    mat = mat @ translate(-np.array(ori))
    return mat


def perspectiveProjection(fovy, aspect, zNear, zFar):
    """
    Compute the perspective projection transformation matrix.
    Parameters:
    - fovy (float): field of view in y direction, in degrees.
    - aspect: aspect ratio of the image (width / height).
    - zNear: z value of the near clipping plane.
    - zFar: z value of the far clipping plane.
    Return:
    - np.array, 4x4 perspective projection transformation matrix.
    """
    fovy = np.radians(fovy)
    f = np.cos(fovy / 2) / np.sin(fovy / 2)
    p_mat = zeros(4)
    p_mat[0, 0] = f / aspect
    p_mat[1, 1] = f
    p_mat[2, 2] = - (zFar + zNear) / (zFar - zNear)
    p_mat[2, 3] = - (2 * zFar * zNear) / (zFar - zNear)
    p_mat[3, 2] = -1

    return p_mat


def orthogonalProjection(left, right, bottom, top, zNear, zFar):
    """
    Compute the orthogonal projection transformation matrix.
    Parameters:
    - left: x value of the left side of the near clipping plane.
    - right: x value of the right side of the near clipping plane.
    - bottom: y value of the bottom side of the near clipping plane.
    - top: y value of the top side of the near clipping plane.
    - zNear: z value of the near clipping plane.
    - zFar: z value of the far clipping plane.
    Return:
    - np.array, 4x4 orthogonal projection transformation matrix.
    """
    o_mat = zeros(4)
    o_mat[0, 0] = 2 / (right - left)
    o_mat[1, 1] = 2 / (top - bottom)
    o_mat[2, 2] = 2 / (zNear - zFar)
    o_mat[0, 3] = - (right + left) / (right - left)
    o_mat[1, 3] = - (top + bottom) / (top - bottom)
    o_mat[2, 3] = - (zNear + zFar) / (zFar - zNear)
    o_mat[3, 3] = 1 
    return o_mat


# -------------------------------------------#
#              End Assignment 1              #
# -------------------------------------------#

# if __name__ == "__main__":
#     print(orthogonalProjection(1, 5, 7, 10, 1, 9))