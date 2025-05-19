#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <cstdio>
#include <string>
#include "../Project4/lab.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace FileOpsTests
{
    TEST_CLASS(UnitTest_FileOps)
    {
    public:

        TEST_METHOD(TestCountLines)
        {
            const string fn = "test_lines.txt";
            ofstream out(fn);
            out << "Line1\nLine2\nLine3\n";
            out.close();

            int lines = countLines(fn);
            Assert::AreEqual(3, lines);

            remove(fn.c_str());
        }

        TEST_METHOD(TestComputeAverageMileage)
        {
            const string fn = "test_mileage.txt";
            ofstream out(fn);
            out << "Toyota 1000 50\nHonda 2000 100\n";
            out.close();

            double avg = computeAverageMileage(fn);
            Assert::AreEqual(75.0, avg, 1e-6);

            remove(fn.c_str());
        }

        TEST_METHOD(TestCountUniqueBrands)
        {
            const string fn = "test_brands.txt";
            ofstream out(fn);
            out << "A 0 0\nB 0 0\nA 0 0\n";
            out.close();

            int uniqueCount = countUniqueBrands(fn);
            Assert::AreEqual(2, uniqueCount);

            remove(fn.c_str());
        }

        TEST_METHOD(TestSelectMinLine)
        {
            const string fn = "test_minline.txt";
            ofstream out(fn);
            out << "Z 0 0\nA 0 0\nM 0 0\n";
            out.close();

            string minLine = selectMinLine(fn);
            Assert::AreEqual(string("A 0 0"), minLine);

            remove(fn.c_str());
        }

        TEST_METHOD(TestSortByBrand)
        {
            const string fn = "test_sort.txt";
            ofstream out(fn);
            out << "B 0 0\nC 0 0\nA 0 0\n";
            out.close();

            sortByBrand(fn);

            ifstream in(fn);
            string l1, l2, l3;
            getline(in, l1);
            getline(in, l2);
            getline(in, l3);
            in.close();

            Assert::AreEqual(string("A 0 0"), l1);
            Assert::AreEqual(string("B 0 0"), l2);
            Assert::AreEqual(string("C 0 0"), l3);

            remove(fn.c_str());
        }
    };
}
