#include "Grid.h"

Grid::Grid(sf::Uint8 cols, sf::Uint8 rows, sf::Uint8 size)
{
	this->rows = rows;
	this->cols = cols;
	this->size = size;
	width = cols * size;
	height = rows * size;

	sf::Color border_color = sf::Color::White;

	border.setPrimitiveType(sf::LineStrip);
	border.append(sf::Vertex(sf::Vector2f(0, 0), border_color));
	border.append(sf::Vertex(sf::Vector2f(width, 0), border_color));
	border.append(sf::Vertex(sf::Vector2f(width, height), border_color));
	border.append(sf::Vertex(sf::Vector2f(0, height), border_color));
	border.append(sf::Vertex(sf::Vector2f(0, 0), border_color));

	grid.setPrimitiveType(sf::Lines);
	for (sf::Uint8 x = 1; x < cols; x++) {
		grid.append(sf::Vertex(sf::Vector2f(x * size, 0), border_color));
		grid.append(sf::Vertex(sf::Vector2f(x * size, height), border_color));
	}
	for (sf::Uint8 y = 1; y < rows; y++) {
		grid.append(sf::Vertex(sf::Vector2f(0, y * size), border_color));
		grid.append(sf::Vertex(sf::Vector2f(width, y * size), border_color));
	}

}

void Grid::showInnerGrid(bool show) {
	innerGridVisible = show;
}

void Grid::showInnerGrid() {
	innerGridVisible = true;
}

void Grid::hideInnerGrid() {
	innerGridVisible = false;
}

bool Grid::isPositionInBounds(sf::Vector2i pos) const
{
	sf::Vector2i npos(pos.x - getPosition().x, pos.y - getPosition().y);

	if (npos.x < 0 || npos.y < 0) {
		return false;
	}

	if (npos.x >= cols * size || npos.y >= rows * size) {
		return false;
	}

	return true;
}

sf::Vector2i Grid::getCellPositionAt(sf::Vector2i pos) const {
	return sf::Vector2i(
		(pos.x - getPosition().x) / size,
		(pos.y - getPosition().y) / size
	);
}

void Grid::setAliveCells(std::vector<sf::Vector2i> positions)
{
	sf::Color cell_color = sf::Color::White;
	cells.clear();
	for (auto cell_pos : positions) {
		sf::Vector2i pos(cell_pos.x * size, cell_pos.y * size);
		cells.setPrimitiveType(sf::Quads);
		cells.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + size), cell_color));
		cells.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), cell_color));
		cells.append(sf::Vertex(sf::Vector2f(pos.x + size, pos.y), cell_color));
		cells.append(sf::Vertex(sf::Vector2f(pos.x + size, pos.y + size), cell_color));
	}
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(border, states);
	if (innerGridVisible) {
		target.draw(grid, states);
	}
	target.draw(cells, states);
}
