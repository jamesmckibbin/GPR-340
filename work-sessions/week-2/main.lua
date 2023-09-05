mode = "fill"

local agents = {}

function checkScreenWrap(agent)
	if agent.x > love.graphics.getWidth() then
		agent.x = 0
	end
	if agent.x < 0 then
		agent.x = love.graphics.getWidth()
	end
	if agent.y > love.graphics.getHeight() then
		agent.y = 0
	end	
	if agent.y < 0 then
		agent.y = love.graphics.getHeight()
	end
end

local crowded_behavior = function(agent, neighbors)
	if #neighbors >= 5 then
		agent.isSurrounded = true
	else
		agent.isSurrounded = false
	end
end

local separation_behavior = function(agent, neighbors)
	local avg = {x=0, y=0}
	for i, other in ipairs(neighbors) do
		avg.x = avg.x + other.x
		avg.y = avg.y + other.y
	end
	avg.x = avg.x / #neighbors
	avg.y = avg.y / #neighbors
	
	local angle = math.atan2(avg.y - agent.y, avg.x - agent.x)
end

function love.load()
	for i = 1, 200 do
		table.insert(agents, {
			x = 64,
			y = 64,
			radius = 8,
			bradius = 12,
			vx = (math.random() * 2 - 1) * 100,
			vy = (math.random() * 2 - 1) * 100,
			isSurrounded = false,
			proximity = 20,
		})
	end
end

function love.update(dt)
	for i, agent in ipairs(agents) do
		local neighbors = {}
		checkScreenWrap(agent)
		for j, other in ipairs(agents) do
			if i ~= j and math.sqrt(math.pow(agent.x - other.x, 2) + math.pow(agent.y - other.y, 2)) <= agent.proximity then
				table.insert(neighbors, other)
			end
		end
		crowded_behavior(agent, neighbors)
		agent.x = agent.x + (agent.vx * dt)
		agent.y = agent.y + (agent.vy * dt)
	end
end

function love.draw()
	for i, agent in ipairs(agents) do
		if agent.isSurrounded then
			love.graphics.setColor(1, 0, 0, 1)
			love.graphics.circle(mode, agent.x, agent.y, agent.bradius)
			love.graphics.setColor(1, 0, 0, 1)
			love.graphics.circle(mode, agent.x, agent.y, agent.radius)
		else
			love.graphics.setColor(1, 1, 0, 1)
			love.graphics.circle(mode, agent.x, agent.y, agent.bradius)
			love.graphics.setColor(0, 1, 1, 1)
			love.graphics.circle(mode, agent.x, agent.y, agent.radius)
		end
	end
end
