#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MainFinal.h"

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

void mock_test(void){
	CU_ASSERT_EQUAL(0,-1);
}

void test_insere(void){ //a funcao busca sera usada para retornar o sucesso da inserção, logo a mesma estará correta se retornar o valor correto. 
   inserir(1); //funções abreEntidade & abreIndice são utilizadas aqui, então devem estar certas para funcionar, lerHeader também é utilizada e deve funcionar para passar o teste.
   CU_ASSERT_EQUAL(buscar(1),0);   
}


void test_atualiza(void){
   atualizar(1);
   CU_ASSERT_EQUAL(buscar(1),0);
}

void test_exclui(void){
   excluir(1);
   CU_ASSERT_EQUAL(buscar(1),0);
}
/************* Test Runner Code goes here **************/

int main ( void ){
   inicializaArvore(); //deve funcionar para as proximas funções funcionarem.
   createHeader(); //para as funçoes funcionarem o header deve ser criado, se o header foi criado então a função está correta
   
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
   if ( (NULL == CU_add_test(pSuite, "Inserir", test_insere)) ||
        (NULL == CU_add_test(pSuite, "atualizar", test_atualiza)) ||
        (NULL == CU_add_test(pSuite, "excluir", test_exclui))
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