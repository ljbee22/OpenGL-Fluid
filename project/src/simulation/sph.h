#ifndef SPH_H
#define SPH_H

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <vector>

#include "particle.h"
#include "consts.h"
#include "spatialHash.h"

using namespace std;

class SPH {
public:
    vector<Particle> &particles;
    Hash hash;
<<<<<<< Updated upstream
    
    SPH(vector<Particle> &_particles): particles(_particles), hash(_particles){}
=======
    SPH(vector<Particle> &_particles): particles(_particles){}
>>>>>>> Stashed changes

    void init() {
        hash.init();
        hash.update();
        computeDensity();
        float max_density = 0.0;
        for (auto &p : particles) {
            max_density = max(max_density, p.density);
        }
        const float WATER_PARTICLE_MASS = WATER_DENSITY / max_density;
        printf("particle mass: %f\n", WATER_PARTICLE_MASS);
        for (auto &p : particles) {
            p.mass = WATER_PARTICLE_MASS;
        }
        computeProperties();
    }
    
    void update(float dt) {
        hash.update();
        computeProperties();
        computeAcceleration();
        for (auto &p : particles) p.update(dt);
    }

private:
    void computeDensity();
    void computeProperties();
    void computeAcceleration();
};

void SPH::computeDensity() {
<<<<<<< Updated upstream
    for (int i=0; i<particles.size(); i++) {
        auto &p = particles[i];
        p.density = 1e-10;
        for (int j : hash.getNN(i)) {
            const auto &p_ = particles[j];
=======
    Hash hash;
    hash.hashing(particles);
    for (auto &p : particles) {
        p.density = 0;
        for (const auto &p_ : hash.neighbor(p)) {
>>>>>>> Stashed changes
            glm::vec3 r = p.pos - p_.pos;
            p.density += p.mass * Consts::poly6Kernel(r);
        }
    }
}

void SPH::computeProperties() {
<<<<<<< Updated upstream
    for (int i=0; i<particles.size(); i++) {
        auto &p = particles[i];
        p.density = 1e-10;
        for (int j : hash.getNN(i)) {
            const auto &p_ = particles[j];
=======
    Hash hash;
    hash.hashing(particles);
    for (auto &p : particles) {
        p.density = 0;
        for (const auto &p_ : hash.neighbor(p)) {
>>>>>>> Stashed changes
            glm::vec3 r = p.pos - p_.pos;
            p.density += p.mass * Consts::poly6Kernel(r);
        }
        
        p.pressure = WATER_GAS_CONSTANT * (p.density - WATER_DENSITY);
    }
}

void SPH::computeAcceleration() {
    for (int i=0; i<particles.size(); i++) {
        auto &p = particles[i];
        p.acc = glm::vec3(0, GRAVITY, 0);
        glm::vec3 acc_pressure = glm::vec3(0, 0, 0);
        glm::vec3 acc_viscosity = glm::vec3(0, 0, 0);
        
<<<<<<< Updated upstream
        for (int j : hash.getNN(i)) {
            const auto &p_ = particles[j];
=======
        for (auto& p_ : hash.neighbor(p)) {
>>>>>>> Stashed changes
            glm::vec3 r = p.pos - p_.pos;
            acc_pressure += Consts::poly6Grad(r) * (p_.mass/p_.density) * ((p.pressure+p_.pressure)/2);
            acc_viscosity += Consts::poly6Lap(r) * (p_.mass/p_.density) * (p.vel-p_.vel);
        }
        
        p.acc -= acc_pressure / p.density;
        p.acc -= acc_viscosity * WATER_VISCOSITY;
    }
}

#endif