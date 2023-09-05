local Grid = require("grid")
local Boids = require("boids")

tilemap = nil
local flock = nil

tile_width = 16
tile_height = 16

function love.load()
	tilemap = Grid.new(64, 64)
	Boids.init(1)
end

function love.update(dt)
	Boids.update(dt)
end

function love.mousepressed(x, y, button)
	local gx = math.floor(x / tile_width)
	local gy = math.floor(y / tile_height)

	tilemap:set(gx, gy, 1)
end

function love.draw()
	for i = 0, tilemap.height do
		for j = 0, tilemap.width do
			local fill = tilemap:get(i, j) == 1 and "fill" or "line"
			love.graphics.rectangle(fill, i * tile_height, j * tile_width, tile_height, tile_width)
		end
	end

	Boids.draw()
end
