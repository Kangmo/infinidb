/* This file is automatically generated by configure.  Do not modify by hand. */
  if (should_init("usmConf")) init_usmConf();

#ifdef USING_AGENTX_MODULE
#ifdef SNMP_TRANSPORT_CALLBACK_DOMAIN
  if (should_init("subagent")) init_subagent();
#endif
#endif

  if (should_init("vacm_conf")) init_vacm_conf();

#ifdef USING_AGENTX_MODULE
  if (should_init("agentx_config")) init_agentx_config();
#endif
