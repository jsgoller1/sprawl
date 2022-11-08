

physics-test-collision-elastic:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-elastic 2>&1 | tee $(MAIN_LOGFILE)

physics-test-collision-elastic-line-up:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-elastic-line-up 2>&1 | tee $(MAIN_LOGFILE)

physics-test-collision-elastic-stack-up:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-elastic-stack-up 2>&1 | tee $(MAIN_LOGFILE)

physics-test-collision-inelastic:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-inelastic 2>&1 | tee $(MAIN_LOGFILE)

physics-test-collision-inelastic-edge-catch:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-inelastic-edge-catch 2>&1 | tee $(MAIN_LOGFILE)

physics-test-gravity:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/gravity 2>&1 | tee $(MAIN_LOGFILE)

physics-tests: \
physics-test-collision-elastic \
physics-test-collision-elastic-line-up \
physics-test-collision-elastic-stack-up \
physics-test-collision-inelastic \
physics-test-collision-inelastic-edge-catch \
physics-test-gravity
