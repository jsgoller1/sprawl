LOGFILE_NAME:=`date --rfc-3339=ns | awk '{print $$2}'`.log

mvp:
	$(ENGINE_BIN) $(DIR)/wads/playtests/mvp 2>&1 | tee $(BIN_DIR)/$@-$(LOGFILE_NAME)

physics-test-collision-elastic:
	$(ENGINE_BIN) $(DIR)/wads/playtests/physics-tests/collision-elastic 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-collision-elastic-line-up:
	$(ENGINE_BIN) $(DIR)/wads/playtests/physics-tests/collision-elastic-line-up 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-collision-elastic-stack-up:
	$(ENGINE_BIN) $(DIR)/wads/playtests/physics-tests/collision-elastic-stack-up 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-collision-inelastic:
	$(ENGINE_BIN) $(DIR)/wads/playtests/physics-tests/collision-inelastic 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-collision-inelastic-edge-catch:
	$(ENGINE_BIN) $(DIR)/wads/playtests/physics-tests/collision-inelastic-edge-catch 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-gravity:
	$(ENGINE_BIN) $(DIR)/wads/playtests/physics-tests/gravity 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-tests: \
physics-test-collision-elastic \
physics-test-collision-elastic-line-up \
physics-test-collision-elastic-stack-up \
physics-test-collision-inelastic \
physics-test-collision-inelastic-edge-catch \
physics-test-gravity
