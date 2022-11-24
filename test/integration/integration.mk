PLAYTEST_DIR:=$(DIR)/test/playtests
LOGFILE_NAME:=`date --rfc-3339=ns | awk '{print $$2}'`.log

mvp:
	$(ENGINE_BIN) $(PLAYTEST_DIR)/mvp 2>&1 | tee $(BIN_DIR)/$@-$(LOGFILE_NAME)

physics-test-collision-elastic:
	$(ENGINE_BIN) $(PLAYTEST_DIR)/physics-tests/collision-elastic 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-collision-elastic-line-up:
	$(ENGINE_BIN) $(PLAYTEST_DIR)/physics-tests/collision-elastic-line-up 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-collision-elastic-stack-up:
	$(ENGINE_BIN) $(PLAYTEST_DIR)/physics-tests/collision-elastic-stack-up 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-collision-inelastic:
	$(ENGINE_BIN) $(PLAYTEST_DIR)/physics-tests/collision-inelastic 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-collision-inelastic-edge-catch:
	$(ENGINE_BIN) $(PLAYTEST_DIR)/physics-tests/collision-inelastic-edge-catch 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-test-gravity:
	$(ENGINE_BIN) $(PLAYTEST_DIR)/physics-tests/gravity 2>&1 | tee $(BIN_DIR)/-$@-$(LOGFILE_NAME)

physics-tests: \
physics-test-collision-elastic \
physics-test-collision-elastic-line-up \
physics-test-collision-elastic-stack-up \
physics-test-collision-inelastic \
physics-test-collision-inelastic-edge-catch \
physics-test-gravity
