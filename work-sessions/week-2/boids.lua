local Boids = { _version = "0.1.0" }

local Agent = require("agent")
local vector = require("vector")

Boids.all = {}

function Boids.init(count)
  for i = 1, count do
    table.insert(Boids.all, Agent.new())
  end
end

local alignment_force = function(neighbors, self)
  -- body
end

local separation_force = function(neighbors, self)
  -- body
end

local cohesion_force = function(neighbors, self)
  -- body
end

local tilemap_avoidance_force = function(neighbors, self)
  local tx = math.floor((self.position.x + self.velocity.x) / tile_width)
  local ty = math.floor((self.position.y + self.velocity.y) / tile_height)
  local nextPos = vector(tx, ty)
  local tilePos = vector(tx + (tile_width * .5), ty + (tile_height * .5))

  local force = vector(0, 0)
  local t = tilemap:get(tx, ty)
  if t == 1 then
    -- left
    if self.position.x < tilePos.x then
        force:add(-1, 0)
        print("left")
    end
    -- under
    if self.position.y < tilePos.y then
        force:add(0, -1)
        print("down")
    end
    -- right
    if self.position.x > tilePos.x then
        force:add(1, 0)
        print("right")
    end
    -- over
    if self.position.y > tilePos.y then
        force:add(0, 1)
        print("up")
    end
  end
  return force
end

-- updates a single boid:
local update_boid = function(dt, neighbors, self)
  -- physics and stuff

  local acceleration = vector(0, 0)

  local avoidance = tilemap_avoidance_force(nil, self)
  acceleration:add(avoidance)

  self.velocity:add(acceleration * dt)
  local speed = self.velocity:magnitude()
  local direction = self.velocity / speed
  self.velocity = direction * 15

  -- update:
  self:update(dt)
end

function Boids.update(dt)
  for i, agent in ipairs(Boids.all) do
    -- get local flock:
    local neighbors = {}
    for j, other in ipairs(Boids.all) do
      if i ~= j then
        local dist = vector.distance(agent.position, other.position)
        if 10 >= dist  then
          table.insert(neighbors, other)
        end
      end
    end

    -- keeps the codebase clean:
    update_boid(dt, neighbors, agent)
  end
end

function Boids.draw()
    for i, agent in ipairs(Boids.all) do
        agent:draw()
    end
end

return Boids