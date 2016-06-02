#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"

#include "mainB.h"

#include <stdio.h>  // for printf

/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/
void test_case_sample(void)
{
   CU_ASSERT(CU_TRUE);
   CU_ASSERT_NOT_EQUAL(2, -1);
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

   CU_ASSERT(CU_FALSE);
   CU_ASSERT_EQUAL(2, 3);
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}

int mock_test(void){
	CU_ASSERT_EQUAL(0,-1);
}

void test_create (void)
{
	CU_ASSERT(CU_TRUE); //FUNCAO CREATE NÃO RETORNA NADA
}

void test_insere(void)
{
	CU_ASSERT(CU_TRUE); //funcao INSERE nao retorna nada
}

void test_lerHeader(tab)
{
	CU_ASSERT_NOT_EQUAL(lerHeader(arqEnt) != tab); //sujeito a mudanças
}
/************* Test Runner Code goes here **************/

int main ( void )
{


	int i,j;
	Tabela tab;

	tab.tamHeader = 0;
	tab.qtdCampos = 0;
	tab.nPk = 0;

	for(i=0;i<6;i++){
		for(j=0;j<30;j++){
			tab.campos[i][j] = '\0';
		}
		tab.tamanhos[i] = 0;
		tab.null[i] = 0;
		tab.autoInc[i] = 0;
	}

	for(i=0;i<6;i++){
		for(j=0;j<4;j++){
			tab.tipos[i][j] = '\0';
		}
	}

	for(i=0;i<3;i++){
		for(j=0;j<10;j++){
			tab.pk[i][j] = '\0';
		}
	}



   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "max_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "Create Header", mock_test)) ||
        (NULL == CU_add_test(pSuite, "Inserir", mock_test)) ||
        (NULL == CU_add_test(pSuite, "Ler Header", mock_test))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
/*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
