#include "SpatialHashGrid.hpp"

SpatialHashGrid::SpatialHashGrid(){
    int numberOfRows = static_cast<int>(sfWindow.getSize().x / cellSize);
    int numberOfColumns = static_cast<int>(sfWindow.getSize().y / cellSize);
    grid.resize(numberOfRows + 2);
    for(auto& column : grid){ 
        column.resize(numberOfColumns + 2);
    }
};

void SpatialHashGrid::insert(const Particle& particle){
    const int cellX = static_cast<int>(particle.getPosition().x / cellSize);
    const int cellY = static_cast<int>(particle.getPosition().y / cellSize);

    grid[cellX][cellY][particle.getColor()].push_back(particle);
}

std::vector<Particle>& SpatialHashGrid::getCellParticles(float* color, int cellX, int cellY){
    return grid[cellX][cellY].at(color);
}

