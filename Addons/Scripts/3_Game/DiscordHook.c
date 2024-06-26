class DiscordHook
{
	// https://discord.com/developers/docs/resources/webhook#execute-webhook
	ref map<string, string> m_alias;

	void DiscordHook()
	{
		m_alias = new map<string, string>;
	}
	
	bool SendHook(string alias, ref DiscordJSON data)
	{
		RestCallback cbx1 = new SilentCallBack;
		RestApi clCore = GetRestApi();

		if (m_alias.Contains(alias))
		{
			if (!clCore)
			{
				clCore = CreateRestApi();
			}
			RestContext ctx = clCore.GetRestContext(m_alias.Get(alias));
			ctx.SetHeader("application/json");
			ctx.POST(cbx1, "", WrapData(data));
			return true;
		}
		return false;
	}

	bool SendHookPlain(string alias, string data)
	{
		RestCallback cbx1 = new SilentCallBack;
		RestApi clCore = GetRestApi();

		if (m_alias.Contains(alias))
		{
			if (!clCore)
			{
				clCore = CreateRestApi();
			}
			RestContext ctx = clCore.GetRestContext(m_alias.Get(alias));
			ctx.SetHeader("application/json");
			ctx.POST(cbx1, "", WrapDataPlain(data));
			return true;
		}
		return false;
	}
	
	private string WrapData(ref DiscordJSON data)
	{
		string json = "{\"embeds\":[";
		
		json += data.GetJSON();
		json += "]}";
		Print(json);
		return json;
	}

	private string WrapDataPlain(string data)
	{
		string json = "{\"content\":\"" + data + "\"}";
		Print(json);
		return json;
	}
	
	// Alias section
	void SetAlias(string alias, string url)
	{
		if (!m_alias.Contains(alias))
		{
			m_alias.Set(alias, url);
		}
	}
	
	void RemoveAlias(string alias)
	{
		if (m_alias.Contains(alias))
		{
			m_alias.Remove(alias);
		}
	}
};

class SilentCallBack : RestCallback
{
	override void OnError(int errorCode) {};
	override void OnTimeout() {};
	override void OnSuccess(string data, int dataSize) {};
};

static ref DiscordHook g_discordHook;
static ref DiscordHook GetDiscordHook()
{
	if (!g_discordHook)
	{
		g_discordHook = new DiscordHook;
	}
	return g_discordHook;
}
