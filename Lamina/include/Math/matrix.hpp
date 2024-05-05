#pragma once
//#include "../Lamina/include/Math/vector.hpp"
#include <iostream>
#include <array>
#include <vector>
#include <stdint.h>
#include <math.h>

#undef NULL
#define NULL 0
#define LM_ROTATE_X_PLANE 0b001
#define LM_ROTATE_Y_PLANE 0b010
#define LM_ROTATE_Z_PLANE 0b100

namespace lm
{
	class Matrix
	{
	public:
		Matrix() : rows(NULL), columns(NULL) {};
		Matrix(uint8_t _rows, uint8_t _columns) : rows(_rows), columns(_columns)
		{
			matrix = std::vector<std::vector<double>>(rows, std::vector<double>(columns, 0));
		}
		~Matrix() {};
		
		void CreateMatrix(const std::vector<std::vector<double>> &_matrix) 
		{
			bool matrixCompatible = true;
			if (_matrix.size() != rows) matrixCompatible = false;
			for (int i = 0; i < _matrix.size(); i++)
			{
				if (_matrix[i].size() != columns) matrixCompatible = false;
			}
			if (matrixCompatible) matrix = _matrix;
			else std::cout << "Unable to assign matix. Incompatible size" << std::endl;
		}
		void ChangeMatrixValue(uint8_t row, uint8_t column, double value) { matrix[row][column] = value; }

		Matrix operator+ (double &scalar)
		{
			Matrix result(rows, columns);
			result.CreateMatrix(matrix);
			for (int i = 0; i < matrix.size(); i++)
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					result.matrix[i][j] += scalar;
				}
			}
			return result;
		}

		Matrix operator+ (Matrix &other)
		{
			Matrix result(rows, columns);
			result.CreateMatrix(matrix);
			for (int i = 0; i < matrix.size(); i++)
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					result.matrix[i][j] += other.matrix[i][j];
				}
			}
			return result;
		}

		Matrix operator- (double &scalar)
		{
			Matrix result(rows, columns);
			result.CreateMatrix(matrix);
			for (int i = 0; i < matrix.size(); i++)
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					result.matrix[i][j] -= scalar;
				}
			}
			return result;
		}

		Matrix operator- (Matrix &other)
		{
			Matrix result(rows, columns);
			result.CreateMatrix(matrix);
			for (int i = 0; i < matrix.size(); i++)
			{
				for (int j = 0; j < matrix[i].size(); j++)
				{
					result.matrix[i][j] -= other.matrix[i][j];
				}
			}
			return result;
		}

		Matrix operator* (Matrix &other)
		{
			if (columns == other.rows)
			{
				std::vector<std::vector<double>> result(rows, std::vector<double>(other.columns, 0));

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < other.columns; j++)
					{
						for (int k = 0; k < rows; k++)
						{
							result[i][j] += matrix[i][k] * other.matrix[k][j];
						}
					}
				}

				Matrix out(rows, other.columns);
				out.CreateMatrix(result);
				return out;
			}
			else 
			{
				std::cout << "Matrices can not be multiplied. Incompatible size." << std::endl;
				return Matrix();
			}
		}

		Matrix operator= (Matrix& other)
		{
			if (this == &other) return *this;

			this->rows = other.rows;
			this->columns = other.columns;
			this->matrix = other.matrix;
			return *this;
		}

		uint8_t rows;
		uint8_t columns;

//		rows ↓		columns ↓
		std::vector<std::vector<double>> matrix;
	};

	class TranslationMatrix
	{
	public:
		TranslationMatrix() : rows(4), columns(4) 
		{ 
			matrix = { {
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			} };
		}

		TranslationMatrix(double x, double y, double z) : rows(4), columns(4)
		{
			matrix = { {
				{1, 0, 0, x},
				{0, 1, 0, y},
				{0, 0, 1, z},
				{0, 0, 0, 1}
			} };
		}

		~TranslationMatrix() {};

		void ChangeTranlationValues(double x, double y, double z)
		{
			matrix = { {
				{1, 0, 0, x},
				{0, 1, 0, y},
				{0, 0, 1, z},
				{0, 0, 0, 1}
			} };
		}

		Matrix operator* (Matrix other)
		{
			if (columns == other.rows)
			{
				std::vector<std::vector<double>> result(rows, std::vector<double>(other.columns, 0));

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < other.columns; j++)
					{
						for (int k = 0; k < rows; k++)
						{
							result[i][j] += matrix[i][k] * other.matrix[k][j];
						}
					}
				}

				Matrix out(rows, other.columns);
				out.CreateMatrix(result);
				return out;
			}
			else
			{
				std::cout << "Matrices can not be multiplied. Incompatible size." << std::endl;
				return Matrix();
			}
		}

		const uint8_t rows;
		const uint8_t columns;

//		rows ↓		columns ↓
		std::array<std::array<double, 4>, 4> matrix;
	};

	class ScaleMatrix
	{
	public:
		ScaleMatrix() : rows(4), columns(4)
		{
			matrix = { {
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			} };
		}
		ScaleMatrix(double x, double y, double z) : rows(4), columns(4)
		{
			matrix = { {
				{x, 0, 0, 0},
				{0, y, 0, 0},
				{0, 0, z, 0},
				{0, 0, 0, 1}
			} };
		}

		~ScaleMatrix() {};

		void ChangeScaleValues(double x, double y, double z)
		{
			matrix = { {
				{x, 0, 0, 0},
				{0, y, 0, 0},
				{0, 0, z, 0},
				{0, 0, 0, 1}
			} };
		}

		Matrix operator* (Matrix other)
		{
			if (columns == other.rows)
			{
				std::vector<std::vector<double>> result(rows, std::vector<double>(other.columns, 0));

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < other.columns; j++)
					{
						for (int k = 0; k < rows; k++)
						{
							result[i][j] += matrix[i][k] * other.matrix[k][j];
						}
					}
				}

				Matrix out(rows, other.columns);
				out.CreateMatrix(result);
				return out;
			}
			else
			{
				std::cout << "Matrices can not be multiplied. Incompatible size." << std::endl;
				return Matrix();
			}
		}

		const uint8_t rows;
		const uint8_t columns;

//		rows ↓		columns ↓
		std::array<std::array<double, 4>, 4> matrix;
	};

	class RotationMatrix
	{
	public:
		RotationMatrix() : rows(4), columns(4)
		{
			matrix = { {
				{1, 0, 0, 0},
				{0, 1, 0, 0},
				{0, 0, 1, 0},
				{0, 0, 0, 1}
			} };
		}
		RotationMatrix(double angle, int plane) : rows(4), columns(4)
		{
			switch (plane)
			{
			case LM_ROTATE_X_PLANE:
				matrix = { {
					{1, 0, 0, 0},
					{0, std::cos(angle), -std::sin(angle), 0},
					{0, std::sin(angle), std::cos(angle), 0},
					{0, 0, 0, 1}
				} };
				break;
			case LM_ROTATE_Y_PLANE:
				matrix = { {
					{std::cos(angle), 0, std::sin(angle), 0},
					{0, 1, 0, 0},
					{-std::sin(angle), 0, std::cos(angle), 0},
					{0, 0, 0, 1}
				} };
				break;
			case LM_ROTATE_Z_PLANE:
				matrix = { {
					{std::cos(angle), -std::sin(angle), 0, 0},
					{std::sin(angle), std::cos(angle), 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 1}
				} };
				break;
			default:
				matrix = { {
					{1, 0, 0, 0},
					{0, 1, 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 1}
				} };
				break;
			}
		}

		~RotationMatrix() {};

		void ChangeRotationAngle(double angle, int plane)
		{
			switch (plane)
			{
			case LM_ROTATE_X_PLANE:
				matrix = { {
					{1, 0, 0, 0},
					{0, std::cos(angle), -std::sin(angle), 0},
					{0, std::sin(angle), std::cos(angle), 0},
					{0, 0, 0, 1}
				} };
				break;
			case LM_ROTATE_Y_PLANE:
				matrix = { {
					{std::cos(angle), 0, std::sin(angle), 0},
					{0, 1, 0, 0},
					{-std::sin(angle), 0, std::cos(angle), 0},
					{0, 0, 0, 1}
				} };
				break;
			case LM_ROTATE_Z_PLANE:
				matrix = { {
					{std::cos(angle), -std::sin(angle), 0, 0},
					{std::sin(angle), std::cos(angle), 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 1}
				} };
				break;
			default:
				matrix = { {
					{1, 0, 0, 0},
					{0, 1, 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 1}
				} };
				break;
			}
		}

		Matrix operator* (Matrix other)
		{
			if (!(columns == other.rows))
			{
				std::vector<std::vector<double>> result(rows, std::vector<double>(other.columns, 0));

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < other.columns; j++)
					{
						for (int k = 0; k < rows; k++)
						{
							result[i][j] += matrix[i][k] * other.matrix[k][j];
						}
					}
				}

				Matrix out(rows, other.columns);
				out.CreateMatrix(result);
				return out;
			}
			else
			{
				std::cout << "Matrices can not be multiplied. Incompatible size." << std::endl;
				return Matrix();
			}
		}

		const uint8_t rows;
		const uint8_t columns;

//		rows ↓		columns ↓
		std::array<std::array<double, 4>, 4> matrix;
	};
}
