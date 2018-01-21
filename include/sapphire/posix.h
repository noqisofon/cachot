#pragma once


/*!
 * 呼び出し元のプロセスの実ユーザー ID を取得します。
 */
SPH_API SPHuser_id_t SPH_get_user_id(void);

/*!
 * 呼び出し元のプロセスの実効ユーザー ID を取得します。
 */
SPH_API SPHuser_id_t SPH_get_execution_user_id(void);
