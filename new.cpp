#include "Matrix.h"
#include <cassert>

void TestSquareMatrix() {
    // Тест конструктора и Get/Set
    SquareMatrix<int> mat(2);
    mat.Set(0, 0, 1);
    mat.Set(0, 1, 2);
    mat.Set(1, 0, 3);
    mat.Set(1, 1, 4);
    std::cout << "Matrix1:\n";
    mat.Print();
    assert(mat.GetSize() == 2);
    assert(mat.Get(0, 0) == 1);
    assert(mat.Get(1, 1) == 4);


    std::cout << "\nMatrix2:\n";
    // Тест сложения
    SquareMatrix<int> mat2 = mat + mat;
    mat2.Print();
    assert(mat2.Get(0, 0) == 2);
    assert(mat2.Get(1, 1) == 8);

    std::cout << "\nMatrix3:\n";
    // Тест умножения
    SquareMatrix<int> mat3 = mat * mat;
    mat3.Print();
    assert(mat3.Get(0, 0) == 7);  // 1*1 + 2*3
    assert(mat3.Get(1, 1) == 22); // 3*2 + 4*4

    // Тест следа
    assert(mat.Trace() == 5); // 1 + 4

    // Тест транспонирования
    SquareMatrix<int> mat4 = mat.Transpose();
    assert(mat4.Get(0, 1) == 3);
    assert(mat4.Get(1, 0) == 2);

    // Тест симметричности
    SquareMatrix<int> symm(2);
    symm.Set(0, 0, 1);
    symm.Set(0, 1, 5);
    symm.Set(1, 0, 5);
    symm.Set(1, 1, 1);
    assert(symm.IsSymmetric());
    assert(!mat.IsSymmetric());

    std::cout << "All SquareMatrix tests passed!\n";
}

int main() {
    try {
        TestSquareMatrix();

        // Пример работы с матрицей
        SquareMatrix<double> mat(3);
        mat.Set(0, 0, 1.5);
        mat.Set(1, 1, 2.5);
        mat.Set(2, 2, 3.5);

        std::cout << "Initial matrix:\n";
        mat.Print();

        std::cout << "\nTransposed matrix:\n";
        mat.Transpose().Print();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }


    //Matrix1 Sequense
    //try {
    //    // Теперь этот код должен работать
    //    SquareMatrix<int> mat(2);
    //    mat.Set(0, 0, 1);
    //    mat.Set(0, 1, 2);
    //    mat.Set(1, 0, 3);
    //    mat.Set(1, 1, 4);

    //    std::cout << "Matrix created successfully!" << std::endl;
    //    return 0;
    //}
    //catch (const std::exception& e) {
    //    std::cerr << "Error: " << e.what() << std::endl;
    //    return 1;
    //}
}

//void TestSquareMatrix() {
//    std::cout << "Testing SquareMatrix...\n";
//
//    // Тест конструктора и Get/Set
//    SquareMatrix<int> mat1(2);
//    mat1.Set(0, 0, 1);
//    mat1.Set(0, 1, 2);
//    mat1.Set(1, 0, 3);
//    mat1.Set(1, 1, 4);
//
//    assert(mat1.Get(0, 0) == 1);
//    assert(mat1.Get(1, 1) == 4);
//
//    // Тест сложения
//    SquareMatrix<int> mat2(2);
//    mat2.Set(0, 0, 5);
//    mat2.Set(0, 1, 6);
//    mat2.Set(1, 0, 7);
//    mat2.Set(1, 1, 8);
//
//    auto mat3 = mat1 + mat2;
//    assert(mat3.Get(0, 0) == 6);
//    assert(mat3.Get(1, 1) == 12);
//
//    // Тест умножения на скаляр
//    auto mat4 = mat1 * 2;
//    assert(mat4.Get(0, 1) == 4);
//
//    // Тест умножения матриц
//    auto mat5 = mat1 * mat2;
//    assert(mat5.Get(0, 0) == 19); // 1*5 + 2*7 = 19
//    assert(mat5.Get(1, 1) == 50); // 3*6 + 4*8 = 50
//
//    // Тест транспонирования
//    auto mat6 = mat1.Transpose();
//    assert(mat6.Get(0, 1) == 3);
//    assert(mat6.Get(1, 0) == 2);
//
//    // Тест следа
//    assert(mat1.Trace() == 5); // 1 + 4 = 5
//
//    // Тест симметричности
//    SquareMatrix<int> mat7(2);
//    mat7.Set(0, 0, 1);
//    mat7.Set(0, 1, 2);
//    mat7.Set(1, 0, 2);
//    mat7.Set(1, 1, 3);
//    assert(mat7.IsSymmetric());
//
//    std::cout << "SquareMatrix tests passed!\n";
//}
//
//int main() {
//    try {
//        TestSquareMatrix();
//
//        std::cout << "All tests passed successfully!\n";
//        return 0;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Test failed: " << e.what() << "\n";
//        return 1;
//    }
//    catch (...) {
//        std::cerr << "Unknown test failure\n";
//        return 1;
//    }
//}

