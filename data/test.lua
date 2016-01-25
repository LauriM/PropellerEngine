function update ( id )
	local value = getPropertyInt(id, "LuaScriptComponent", "TestInt");
	local scriptname = getPropertyString(id, "LuaScriptComponent", "ScriptName");

	--logWarning(tostring(scriptname) .. " = value is: " .. tostring(value));

	value = value + 1;

	setPropertyInt(id, "LuaScriptComponent", "TestInt", value);
end
