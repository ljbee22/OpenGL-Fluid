#pragma once
#include <vector>
#include "particle.h"

class Cell {
public:
	Cell() {
		pa = new Particle[10];
		capacity = 10;
		size = 0;
		s = 0;
	}
	~Cell() {
		delete[] pa;
	}
	void insert(Particle p) {
		if (capacity == size) {
			Particle* temp = new Particle[capacity * 2];
			for (int i = 0; i < capacity; i++) {
				temp[i] = pa[i];
			}
			capacity *= 2;
			delete[] pa;
			pa = temp;
		}
		pa[size++] = p;
		s = size;
	}
	Particle pop() {
		return pa[--s];
	}
	int getSize() {
		return s;
	}
	void resetS() {
		s = size;
	}
	void reset() {
		size = 0;
		s = 0;
	}
private:
	Particle* pa;
	int capacity;
	int size;
	int s;
};

class Hash {
public:
	Hash() {
		nx = (BOUNDARY + 1) * 2;
		ny = (BOUNDARY + 1) * 2;
		nz = (BOUNDARY + 1) * 2;
		n = nx * ny * nz;
		cellCount = new int[n];
		for (int i = 0; i < n; i++) {
			cellCount[i] = 0;
		}
		cells = new Cell[n];
	}

	~Hash() {
		delete[] cellCount;
		delete[] cells;
	}

	void hashing(vector<Particle> pv) {
		int i;
		for (auto& p : pv) {
			int xi = floor(p.pos.x + BOUNDARY + 1);
			int yi = floor(p.pos.y + BOUNDARY + 1);
			int zi = floor(p.pos.z + BOUNDARY + 1);
			i = (xi * ny + yi) * nz + zi;
			cellCount[i]++;
			cells[i].insert(p);
		}
	}

	vector<Particle> neighbor(Particle p) {
		int xi = floor(p.pos.x + BOUNDARY + 1);
		int yi = floor(p.pos.y + BOUNDARY + 1);
		int zi = floor(p.pos.z + BOUNDARY + 1);
		vector<Particle> pv;
		int num = 0;
		for (int xi_ = xi - 1; xi_ <= xi + 1; xi_++) {
			if (xi_ < 0 || xi >= nx) continue;
			for (int yi_ = yi - 1; yi_ <= yi + 1; yi_++) {
				if (yi_ < 0 || yi >= ny) continue;
				for (int zi_ = zi - 1; zi_ <= zi + 1; zi_++) {
					if (zi_ < 0 || zi >= nz) continue;
					int i = (xi_ * ny + yi_) * nz + zi_;
					while (cells[i].getSize() > 0) {
						num++;
						pv.push_back(cells[i].pop());
					}
					cells[i].resetS();
				}
			}
		}
		return pv;
	}

	void print() {
		for (int i = 0; i < n; i++) {
			printf("%d : %d ", i, cellCount[i]);
			if (i % 10 == 0) printf("\n");
		}
	}

	void reset() {
		for (int i = 0; i < n; i++) {
			cellCount[i] = 0;
			cells[i].reset();
		}
	}

private:
	//Particle* particles;
	Cell* cells;
	int* cellCount;
	int nx;
	int ny;
	int nz;
	int n;
};