void* SonarThread(void* Param)

{

	bool run = true;
	while(run)
	{
   		if(sonar<=20)
      	{
		sonarState = 1;
	  	}
    		else
      	{
		sonarState = 0;
	  	}
  	}
	pthread_exit(NULL);

}
