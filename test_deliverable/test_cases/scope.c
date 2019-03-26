int func(){
	int a = 2;
	{
		int b = 10;
		{
			int c = 5;
			{
				int d = 5;
				{
					int e = 5;
					{
						int f = 5;
						a += f;
					}
					a += e;
				}
				a += d;
			}
			a += c;
		}
		a += b;
	}
	{
		int b = 20;
		a += b;
	}
	return a;
}