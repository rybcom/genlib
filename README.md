declarative generation of class domain model


	START_MODEL_CLASS(Object);
	ADD_PROPERTY(Jezik, int);
	ADD_PROPERTY(Bazik, float);
	ADD_PROPERTY(Dazdik, std::string);
	END_MODEL_CLASS();

	START_MODEL_CLASS(Airplane);
	ADD_PROPERTY(age, int);
	ADD_PROPERTY(max_speed, float);
	ADD_PROPERTY(min_speed, float);
	ADD_PROPERTY(max_angle, float);
	ADD_PROPERTY(min_angle, float);
	END_MODEL_CLASS();

	START_MODEL_CLASS(Person);
	ADD_PROPERTY(age, int);
	ADD_PROPERTY(surname, std::string);
	ADD_PROPERTY(firstname, std::string);
	ADD_PROPERTY(address, std::string);
	ADD_PROPERTY(score,double);
	END_MODEL_CLASS();# genlib
